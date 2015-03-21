// <Copyright Holder>. Copyright (C) <Copyright Year(s)>. <License>
#ifndef HEADER_RECON_VERSION_H_INCLUDED
#define HEADER_RECON_VERSION_H_INCLUDED

#ifdef __cplusplus
#   define EXTERNC extern "C"
#else
#   define EXTERNC
#endif

EXTERNC int recon_version_major();
EXTERNC int recon_version_minor();
EXTERNC int recon_version_patch();

#endif
