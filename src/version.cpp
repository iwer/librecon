#include <recon/version.h>
#include "libraryinfo.h"

EXTERNC int recon_version_major()
{ 
    return APPLICATION_VERSION_MAJOR; 
}

EXTERNC int recon_version_minor()
{
    return APPLICATION_VERSION_MINOR;
}

EXTERNC int recon_version_patch()
{
    return APPLICATION_VERSION_PATCH;
}
