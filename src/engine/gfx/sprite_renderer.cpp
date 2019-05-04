#include "sprite_renderer.h"
#include "../tools/loader.h"
#include <algorithm>
#include <execution>

namespace le
{

const unsigned int MAX_INSTANCES = 200000;
const unsigned int INSTACE_DATA_LENGTH = 19; // MODEL MATRIX (4x4 = 16) + Tint (3 floats)
float SpriteRenderer::buffer[INSTACE_DATA_LENGTH * MAX_INSTANCES];

float vertices[] = { 
    // Pos      // Tex
    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 0.0f, 0.0f, 

    0.0f, 1.0f, 0.0f, 1.0f,
    1.0f, 1.0f, 1.0f, 1.0f,
    1.0f, 0.0f, 1.0f, 0.0f
};

SpriteRenderer::SpriteRenderer(Shader &shader)
{
    this->shader = shader;
    this->shader.BindAttribute("vertex", 0);
    this->shader.BindAttribute("model", 1);
    this->shader.BindAttribute("spriteColor", 5); 
    this->initRenderData();	
}

void SpriteRenderer::initRenderData()
{
    this->vbo = Loader::CreateEmptyVBO(INSTACE_DATA_LENGTH * MAX_INSTANCES);
    this->quadVAO = Loader::LoadToVAO(vertices, 4, 24)->VaoID;
    
    // Model matrix
    Loader::AddInstancedAttributes(this->quadVAO, this->vbo, 1, 4, INSTACE_DATA_LENGTH, 0);
    Loader::AddInstancedAttributes(this->quadVAO, this->vbo, 2, 4, INSTACE_DATA_LENGTH, 4);
    Loader::AddInstancedAttributes(this->quadVAO, this->vbo, 3, 4, INSTACE_DATA_LENGTH, 8);
    Loader::AddInstancedAttributes(this->quadVAO, this->vbo, 4, 4, INSTACE_DATA_LENGTH, 12);
    
    Loader::AddInstancedAttributes(this->quadVAO, this->vbo, 5, 3, INSTACE_DATA_LENGTH, 16);
}

void SpriteRenderer::Prepare()
{
    this->shader.Use();
    glBindVertexArray(this->quadVAO);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
    glEnableVertexAttribArray(3);
    glEnableVertexAttribArray(4);
    glEnableVertexAttribArray(5);

    glEnable(GL_BLEND);
    glDepthMask(GL_FALSE);
}

void SpriteRenderer::StoreMatrixData(const glm::mat4& _matrix)
{
    buffer[bufferPointer++] = _matrix[0][0];
    buffer[bufferPointer++] = _matrix[0][1];
    buffer[bufferPointer++] = _matrix[0][2];
    buffer[bufferPointer++] = _matrix[0][3];

    buffer[bufferPointer++] = _matrix[1][0];
    buffer[bufferPointer++] = _matrix[1][1];
    buffer[bufferPointer++] = _matrix[1][2];
    buffer[bufferPointer++] = _matrix[1][3];

    buffer[bufferPointer++] = _matrix[2][0];
    buffer[bufferPointer++] = _matrix[2][1];
    buffer[bufferPointer++] = _matrix[2][2];
    buffer[bufferPointer++] = _matrix[2][3];

    buffer[bufferPointer++] = _matrix[3][0];
    buffer[bufferPointer++] = _matrix[3][1];
    buffer[bufferPointer++] = _matrix[3][2];
    buffer[bufferPointer++] = _matrix[3][3];
}

void SpriteRenderer::UpdateTintInfo(Sprite* sprite)
{
    buffer[bufferPointer++] = sprite->tint.x;
    buffer[bufferPointer++] = sprite->tint.y;
    buffer[bufferPointer++] = sprite->tint.z;
}

void SpriteRenderer::computeModels(std::vector<Sprite*>& sprites)
{
    for(Sprite* s : sprites)
    {
        s->ComputeModel();
        StoreMatrixData(s->model);
        UpdateTintInfo(s);
    }
}

void SpriteRenderer::Render(std::vector<Sprite*>& sprites)
{
    Prepare();

    glActiveTexture(GL_TEXTURE0);
    sprites[0]->texture->Bind();
	bufferPointer = 0;
	
	computeModels(sprites);

    Loader::UpdateVBO(vbo, buffer, sprites.size() * INSTACE_DATA_LENGTH);
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, sprites.size());
    FinishRendering();
} 

void SpriteRenderer::FinishRendering()
{
    glDepthMask(true);
    glDisable(GL_BLEND);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    glDisableVertexAttribArray(3);
    glDisableVertexAttribArray(4);
    glDisableVertexAttribArray(5);
    glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->quadVAO);
}


}