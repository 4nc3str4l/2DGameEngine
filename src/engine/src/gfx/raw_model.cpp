
#include "raw_model.h"
#include "../tools/log.h"

namespace le
{
RawModel::RawModel(int _vaoID, int _vertexCount)
{
    VaoID = _vaoID;
    VertexCount = _vertexCount;
    LOG_INFO("VAO id :",  VaoID);
}
}
