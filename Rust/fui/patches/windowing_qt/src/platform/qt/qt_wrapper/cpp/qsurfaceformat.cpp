#include "qsurfaceformat.h"
#include <QSurfaceFormat>

void QSurfaceFormat_setDefault(int stencilBufferSize, int depthBufferSize)
{
    QSurfaceFormat format;
    format.setStencilBufferSize(stencilBufferSize);
	format.setDepthBufferSize(depthBufferSize);
    QSurfaceFormat::setDefaultFormat(format);
}
