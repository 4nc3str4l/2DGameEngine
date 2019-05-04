#pragma once 

#include <glad/glad.h>
#include "shader.h"
#include "sprite.h"
#include "glm/glm.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "texture_2d.h"
#include <vector>

namespace le 
{
class SpriteRenderer
{
    public:
        SpriteRenderer(Shader &shader);
        ~SpriteRenderer();
        void Render(std::vector<Sprite*>& sprites);
    private:
        void Prepare();
        void StoreMatrixData(const glm::mat4& _matrix);
        void UpdateTintInfo(Sprite* sprite);
        void FinishRendering();
    private:
        Shader shader; 
        GLuint quadVAO;
        GLuint vbo;
		unsigned int bufferPointer;
		static float buffer[];
        void initRenderData();
        void computeModels(std::vector<Sprite*>& sprites);
};
}
