#pragma once

#include <QtCore/qglobal.h>

#if defined(MODELVAR_LIBRARY)
# define MODELVARSHARED_EXPORT Q_DECL_EXPORT
#else
# define MODELVARSHARED_EXPORT Q_DECL_IMPORT
#endif