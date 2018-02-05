/*
** Lua binding: ExtensionsSpine
** Generated automatically by tolua++-1.0.92 on Mon Feb  5 19:59:10 2018.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

/* Exported function */
TOLUA_API int  tolua_ExtensionsSpine_open (lua_State* tolua_S);

#include "spine/SkeletonAnimation.h"
using namespace spine;

/* function to release collected object via destructor */
#ifdef __cplusplus

static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}
#endif


/* function to register type */
static void tolua_reg_types (lua_State* tolua_S)
{
 tolua_usertype(tolua_S,"SkeletonAnimation");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(SkeletonAnimation)), "SkeletonAnimation");
 tolua_usertype(tolua_S,"spAnimationStateData");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spAnimationStateData)), "spAnimationStateData");
 tolua_usertype(tolua_S,"std::function<void(int trackIndex)>");
 tolua_usertype(tolua_S,"spAttachment");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spAttachment)), "spAttachment");
 tolua_usertype(tolua_S,"std::function<void(int trackIndex, spEvent* event)>");
 tolua_usertype(tolua_S,"CCNode");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCNode)), "CCNode");
 tolua_usertype(tolua_S,"std::function<void(int trackIndex, int loopCount)>");
 tolua_usertype(tolua_S,"spTrackEntry");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spTrackEntry)), "spTrackEntry");
 tolua_usertype(tolua_S,"spSkeletonData");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spSkeletonData)), "spSkeletonData");
 tolua_usertype(tolua_S,"ccBlendFunc");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(ccBlendFunc)), "ccBlendFunc");
 tolua_usertype(tolua_S,"spEvent");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spEvent)), "spEvent");
 tolua_usertype(tolua_S,"spEventType");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spEventType)), "spEventType");
 tolua_usertype(tolua_S,"spBone");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spBone)), "spBone");
 tolua_usertype(tolua_S,"spSlot");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spSlot)), "spSlot");
 tolua_usertype(tolua_S,"CCBlendProtocol");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(CCBlendProtocol)), "CCBlendProtocol");
 tolua_usertype(tolua_S,"SkeletonRenderer");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(SkeletonRenderer)), "SkeletonRenderer");
 tolua_usertype(tolua_S,"spAtlas");
 toluafix_add_type_mapping(CLASS_HASH_CODE(typeid(spAtlas)), "spAtlas");
}

/* method: createWithData of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_createWithData00
static int tolua_ExtensionsSpine_SkeletonRenderer_createWithData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spSkeletonData",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,3,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  spSkeletonData* skeletonData = ((spSkeletonData*)  tolua_tousertype(tolua_S,2,0));
  bool ownsSkeletonData = ((bool)  tolua_toboolean(tolua_S,3,false));
  {
   SkeletonRenderer* tolua_ret = (SkeletonRenderer*)  SkeletonRenderer::createWithData(skeletonData,ownsSkeletonData);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonRenderer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithFile of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_createWithFile00
static int tolua_ExtensionsSpine_SkeletonRenderer_createWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"spAtlas",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* skeletonDataFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  spAtlas* atlas = ((spAtlas*)  tolua_tousertype(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   SkeletonRenderer* tolua_ret = (SkeletonRenderer*)  SkeletonRenderer::createWithFile(skeletonDataFile,atlas,scale);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonRenderer");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithFile of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_createWithFile01
static int tolua_ExtensionsSpine_SkeletonRenderer_createWithFile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* skeletonDataFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* atlasFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   SkeletonRenderer* tolua_ret = (SkeletonRenderer*)  SkeletonRenderer::createWithFile(skeletonDataFile,atlasFile,scale);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonRenderer");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsSpine_SkeletonRenderer_createWithFile00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: updateWorldTransform of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_updateWorldTransform00
static int tolua_ExtensionsSpine_SkeletonRenderer_updateWorldTransform00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'updateWorldTransform'", NULL);
#endif
  {
   self->updateWorldTransform();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'updateWorldTransform'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setToSetupPose of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setToSetupPose00
static int tolua_ExtensionsSpine_SkeletonRenderer_setToSetupPose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setToSetupPose'", NULL);
#endif
  {
   self->setToSetupPose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setToSetupPose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBonesToSetupPose of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setBonesToSetupPose00
static int tolua_ExtensionsSpine_SkeletonRenderer_setBonesToSetupPose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBonesToSetupPose'", NULL);
#endif
  {
   self->setBonesToSetupPose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBonesToSetupPose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSlotsToSetupPose of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setSlotsToSetupPose00
static int tolua_ExtensionsSpine_SkeletonRenderer_setSlotsToSetupPose00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSlotsToSetupPose'", NULL);
#endif
  {
   self->setSlotsToSetupPose();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSlotsToSetupPose'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findBone of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_findBone00
static int tolua_ExtensionsSpine_SkeletonRenderer_findBone00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* boneName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findBone'", NULL);
#endif
  {
   spBone* tolua_ret = (spBone*)  self->findBone(boneName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spBone");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findBone'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: findSlot of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_findSlot00
static int tolua_ExtensionsSpine_SkeletonRenderer_findSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'findSlot'", NULL);
#endif
  {
   spSlot* tolua_ret = (spSlot*)  self->findSlot(slotName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spSlot");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'findSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setSkin of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setSkin00
static int tolua_ExtensionsSpine_SkeletonRenderer_setSkin00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* skinName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setSkin'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setSkin(skinName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setSkin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getAttachment of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_getAttachment00
static int tolua_ExtensionsSpine_SkeletonRenderer_getAttachment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* attachmentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getAttachment'", NULL);
#endif
  {
   spAttachment* tolua_ret = (spAttachment*)  self->getAttachment(slotName,attachmentName);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spAttachment");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getAttachment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAttachment of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setAttachment00
static int tolua_ExtensionsSpine_SkeletonRenderer_setAttachment00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* attachmentName = ((const char*)  tolua_tostring(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAttachment'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->setAttachment(slotName,attachmentName);
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAttachment'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getBlendFunc of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_getBlendFunc00
static int tolua_ExtensionsSpine_SkeletonRenderer_getBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getBlendFunc'", NULL);
#endif
  {
   ccBlendFunc tolua_ret = (ccBlendFunc)  self->getBlendFunc();
   {
#ifdef __cplusplus
    void* tolua_obj = Mtolua_new((ccBlendFunc)(tolua_ret));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#else
    void* tolua_obj = tolua_copy(tolua_S,(void*)&tolua_ret,sizeof(ccBlendFunc));
     tolua_pushusertype(tolua_S,tolua_obj,"ccBlendFunc");
    tolua_register_gc(tolua_S,lua_gettop(tolua_S));
#endif
   }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setBlendFunc of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setBlendFunc00
static int tolua_ExtensionsSpine_SkeletonRenderer_setBlendFunc00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"ccBlendFunc",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  ccBlendFunc var = *((ccBlendFunc*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setBlendFunc'", NULL);
#endif
  {
   self->setBlendFunc(var);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setBlendFunc'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setOpacityModifyRGB of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_setOpacityModifyRGB00
static int tolua_ExtensionsSpine_SkeletonRenderer_setOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isboolean(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  bool value = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setOpacityModifyRGB'", NULL);
#endif
  {
   self->setOpacityModifyRGB(value);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: isOpacityModifyRGB of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_isOpacityModifyRGB00
static int tolua_ExtensionsSpine_SkeletonRenderer_isOpacityModifyRGB00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'isOpacityModifyRGB'", NULL);
#endif
  {
   bool tolua_ret = (bool)  self->isOpacityModifyRGB();
   tolua_pushboolean(tolua_S,(bool)tolua_ret);
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'isOpacityModifyRGB'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getNodeForSlot of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonRenderer_getNodeForSlot00
static int tolua_ExtensionsSpine_SkeletonRenderer_getNodeForSlot00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonRenderer",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
  const char* slotName = ((const char*)  tolua_tostring(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getNodeForSlot'", NULL);
#endif
  {
   CCNode* tolua_ret = (CCNode*)  self->getNodeForSlot(slotName);
    int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret,"CCNode");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getNodeForSlot'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* get function: __CCBlendProtocol__ of class  SkeletonRenderer */
#ifndef TOLUA_DISABLE_tolua_get_SkeletonRenderer___CCBlendProtocol__
static int tolua_get_SkeletonRenderer___CCBlendProtocol__(lua_State* tolua_S)
{
  SkeletonRenderer* self = (SkeletonRenderer*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in accessing variable '__CCBlendProtocol__'",NULL);
#endif
#ifdef __cplusplus
   tolua_pushusertype(tolua_S,(void*)static_cast<CCBlendProtocol*>(self), "CCBlendProtocol");
#else
   tolua_pushusertype(tolua_S,(void*)((CCBlendProtocol*)self), "CCBlendProtocol");
#endif
 return 1;
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithData of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_createWithData00
static int tolua_ExtensionsSpine_SkeletonAnimation_createWithData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spSkeletonData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  spSkeletonData* skeletonData = ((spSkeletonData*)  tolua_tousertype(tolua_S,2,0));
  {
   SkeletonAnimation* tolua_ret = (SkeletonAnimation*)  SkeletonAnimation::createWithData(skeletonData);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithFile of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_createWithFile00
static int tolua_ExtensionsSpine_SkeletonAnimation_createWithFile00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isusertype(tolua_S,3,"spAtlas",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  const char* skeletonDataFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  spAtlas* atlas = ((spAtlas*)  tolua_tousertype(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   SkeletonAnimation* tolua_ret = (SkeletonAnimation*)  SkeletonAnimation::createWithFile(skeletonDataFile,atlas,scale);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonAnimation");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'createWithFile'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: createWithFile of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_createWithFile01
static int tolua_ExtensionsSpine_SkeletonAnimation_createWithFile01(lua_State* tolua_S)
{
 tolua_Error tolua_err;
 if (
     !tolua_isusertable(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
 {
  const char* skeletonDataFile = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* atlasFile = ((const char*)  tolua_tostring(tolua_S,3,0));
  float scale = ((float)  tolua_tonumber(tolua_S,4,0));
  {
   SkeletonAnimation* tolua_ret = (SkeletonAnimation*)  SkeletonAnimation::createWithFile(skeletonDataFile,atlasFile,scale);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"SkeletonAnimation");
  }
 }
 return 1;
tolua_lerror:
 return tolua_ExtensionsSpine_SkeletonAnimation_createWithFile00(tolua_S);
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimationStateData of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setAnimationStateData00
static int tolua_ExtensionsSpine_SkeletonAnimation_setAnimationStateData00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spAnimationStateData",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  spAnimationStateData* stateData = ((spAnimationStateData*)  tolua_tousertype(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimationStateData'", NULL);
#endif
  {
   self->setAnimationStateData(stateData);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimationStateData'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setMix of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setMix00
static int tolua_ExtensionsSpine_SkeletonAnimation_setMix00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isstring(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  const char* fromAnimation = ((const char*)  tolua_tostring(tolua_S,2,0));
  const char* toAnimation = ((const char*)  tolua_tostring(tolua_S,3,0));
  float duration = ((float)  tolua_tonumber(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setMix'", NULL);
#endif
  {
   self->setMix(fromAnimation,toAnimation,duration);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setMix'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setAnimation of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setAnimation00
static int tolua_ExtensionsSpine_SkeletonAnimation_setAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,5,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,4,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAnimation'", NULL);
#endif
  {
   spTrackEntry* tolua_ret = (spTrackEntry*)  self->setAnimation(trackIndex,name,loop);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spTrackEntry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: addAnimation of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_addAnimation00
static int tolua_ExtensionsSpine_SkeletonAnimation_addAnimation00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     !tolua_isstring(tolua_S,3,0,&tolua_err) ||
     !tolua_isboolean(tolua_S,4,0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  const char* name = ((const char*)  tolua_tostring(tolua_S,3,0));
  bool loop = ((bool)  tolua_toboolean(tolua_S,4,0));
  float delay = ((float)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'addAnimation'", NULL);
#endif
  {
   spTrackEntry* tolua_ret = (spTrackEntry*)  self->addAnimation(trackIndex,name,loop,delay);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spTrackEntry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'addAnimation'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getCurrent of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_getCurrent00
static int tolua_ExtensionsSpine_SkeletonAnimation_getCurrent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getCurrent'", NULL);
#endif
  {
   spTrackEntry* tolua_ret = (spTrackEntry*)  self->getCurrent(trackIndex);
    tolua_pushusertype(tolua_S,(void*)tolua_ret,"spTrackEntry");
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getCurrent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearTracks of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_clearTracks00
static int tolua_ExtensionsSpine_SkeletonAnimation_clearTracks00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearTracks'", NULL);
#endif
  {
   self->clearTracks();
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearTracks'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: clearTrack of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_clearTrack00
static int tolua_ExtensionsSpine_SkeletonAnimation_clearTrack00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,1,&tolua_err) ||
     !tolua_isnoobj(tolua_S,3,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'clearTrack'", NULL);
#endif
  {
   self->clearTrack(trackIndex);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'clearTrack'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setStartListener of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setStartListener00
static int tolua_ExtensionsSpine_SkeletonAnimation_setStartListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spTrackEntry",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::function<void(int trackIndex)>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  spTrackEntry* entry = ((spTrackEntry*)  tolua_tousertype(tolua_S,2,0));
   std::function<void(int trackIndex)> listener = *((  std::function<void(int trackIndex)>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setStartListener'", NULL);
#endif
  {
   self->setStartListener(entry,listener);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setStartListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEndListener of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setEndListener00
static int tolua_ExtensionsSpine_SkeletonAnimation_setEndListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spTrackEntry",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::function<void(int trackIndex)>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  spTrackEntry* entry = ((spTrackEntry*)  tolua_tousertype(tolua_S,2,0));
   std::function<void(int trackIndex)> listener = *((  std::function<void(int trackIndex)>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEndListener'", NULL);
#endif
  {
   self->setEndListener(entry,listener);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEndListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setCompleteListener of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setCompleteListener00
static int tolua_ExtensionsSpine_SkeletonAnimation_setCompleteListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spTrackEntry",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::function<void(int trackIndex, int loopCount)>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  spTrackEntry* entry = ((spTrackEntry*)  tolua_tousertype(tolua_S,2,0));
   std::function<void(int trackIndex, int loopCount)> listener = *((  std::function<void(int trackIndex, int loopCount)>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setCompleteListener'", NULL);
#endif
  {
   self->setCompleteListener(entry,listener);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setCompleteListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setEventListener of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_setEventListener00
static int tolua_ExtensionsSpine_SkeletonAnimation_setEventListener00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isusertype(tolua_S,2,"spTrackEntry",0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"std::function<void(int trackIndex, spEvent* event)>",0,&tolua_err)) ||
     !tolua_isnoobj(tolua_S,4,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  spTrackEntry* entry = ((spTrackEntry*)  tolua_tousertype(tolua_S,2,0));
   std::function<void(int trackIndex, spEvent* event)> listener = *((  std::function<void(int trackIndex, spEvent* event)>*)  tolua_tousertype(tolua_S,3,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setEventListener'", NULL);
#endif
  {
   self->setEventListener(entry,listener);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setEventListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onAnimationStateEvent of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_onAnimationStateEvent00
static int tolua_ExtensionsSpine_SkeletonAnimation_onAnimationStateEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"spEventType",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"spEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  spEventType type = *((spEventType*)  tolua_tousertype(tolua_S,3,0));
  spEvent* event = ((spEvent*)  tolua_tousertype(tolua_S,4,0));
  int loopCount = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onAnimationStateEvent'", NULL);
#endif
  {
   self->onAnimationStateEvent(trackIndex,type,event,loopCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onAnimationStateEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: onTrackEntryEvent of class  SkeletonAnimation */
#ifndef TOLUA_DISABLE_tolua_ExtensionsSpine_SkeletonAnimation_onTrackEntryEvent00
static int tolua_ExtensionsSpine_SkeletonAnimation_onTrackEntryEvent00(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"SkeletonAnimation",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,2,0,&tolua_err) ||
     (tolua_isvaluenil(tolua_S,3,&tolua_err) || !tolua_isusertype(tolua_S,3,"spEventType",0,&tolua_err)) ||
     !tolua_isusertype(tolua_S,4,"spEvent",0,&tolua_err) ||
     !tolua_isnumber(tolua_S,5,0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,6,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  SkeletonAnimation* self = (SkeletonAnimation*)  tolua_tousertype(tolua_S,1,0);
  int trackIndex = ((int)  tolua_tonumber(tolua_S,2,0));
  spEventType type = *((spEventType*)  tolua_tousertype(tolua_S,3,0));
  spEvent* event = ((spEvent*)  tolua_tousertype(tolua_S,4,0));
  int loopCount = ((int)  tolua_tonumber(tolua_S,5,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'onTrackEntryEvent'", NULL);
#endif
  {
   self->onTrackEntryEvent(trackIndex,type,event,loopCount);
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'onTrackEntryEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* Open function */
TOLUA_API int tolua_ExtensionsSpine_open (lua_State* tolua_S)
{
 tolua_open(tolua_S);
 tolua_reg_types(tolua_S);
 tolua_module(tolua_S,NULL,0);
 tolua_beginmodule(tolua_S,NULL);
  tolua_cclass(tolua_S,"SkeletonRenderer","SkeletonRenderer","CCNode",NULL);
  tolua_beginmodule(tolua_S,"SkeletonRenderer");
   tolua_function(tolua_S,"createWithData",tolua_ExtensionsSpine_SkeletonRenderer_createWithData00);
   tolua_function(tolua_S,"createWithFile",tolua_ExtensionsSpine_SkeletonRenderer_createWithFile00);
   tolua_function(tolua_S,"createWithFile",tolua_ExtensionsSpine_SkeletonRenderer_createWithFile01);
   tolua_function(tolua_S,"updateWorldTransform",tolua_ExtensionsSpine_SkeletonRenderer_updateWorldTransform00);
   tolua_function(tolua_S,"setToSetupPose",tolua_ExtensionsSpine_SkeletonRenderer_setToSetupPose00);
   tolua_function(tolua_S,"setBonesToSetupPose",tolua_ExtensionsSpine_SkeletonRenderer_setBonesToSetupPose00);
   tolua_function(tolua_S,"setSlotsToSetupPose",tolua_ExtensionsSpine_SkeletonRenderer_setSlotsToSetupPose00);
   tolua_function(tolua_S,"findBone",tolua_ExtensionsSpine_SkeletonRenderer_findBone00);
   tolua_function(tolua_S,"findSlot",tolua_ExtensionsSpine_SkeletonRenderer_findSlot00);
   tolua_function(tolua_S,"setSkin",tolua_ExtensionsSpine_SkeletonRenderer_setSkin00);
   tolua_function(tolua_S,"getAttachment",tolua_ExtensionsSpine_SkeletonRenderer_getAttachment00);
   tolua_function(tolua_S,"setAttachment",tolua_ExtensionsSpine_SkeletonRenderer_setAttachment00);
   tolua_function(tolua_S,"getBlendFunc",tolua_ExtensionsSpine_SkeletonRenderer_getBlendFunc00);
   tolua_function(tolua_S,"setBlendFunc",tolua_ExtensionsSpine_SkeletonRenderer_setBlendFunc00);
   tolua_function(tolua_S,"setOpacityModifyRGB",tolua_ExtensionsSpine_SkeletonRenderer_setOpacityModifyRGB00);
   tolua_function(tolua_S,"isOpacityModifyRGB",tolua_ExtensionsSpine_SkeletonRenderer_isOpacityModifyRGB00);
   tolua_function(tolua_S,"getNodeForSlot",tolua_ExtensionsSpine_SkeletonRenderer_getNodeForSlot00);
   tolua_variable(tolua_S,"__CCBlendProtocol__",tolua_get_SkeletonRenderer___CCBlendProtocol__,NULL);
  tolua_endmodule(tolua_S);
  tolua_cclass(tolua_S,"SkeletonAnimation","SkeletonAnimation","SkeletonRenderer",NULL);
  tolua_beginmodule(tolua_S,"SkeletonAnimation");
   tolua_function(tolua_S,"createWithData",tolua_ExtensionsSpine_SkeletonAnimation_createWithData00);
   tolua_function(tolua_S,"createWithFile",tolua_ExtensionsSpine_SkeletonAnimation_createWithFile00);
   tolua_function(tolua_S,"createWithFile",tolua_ExtensionsSpine_SkeletonAnimation_createWithFile01);
   tolua_function(tolua_S,"setAnimationStateData",tolua_ExtensionsSpine_SkeletonAnimation_setAnimationStateData00);
   tolua_function(tolua_S,"setMix",tolua_ExtensionsSpine_SkeletonAnimation_setMix00);
   tolua_function(tolua_S,"setAnimation",tolua_ExtensionsSpine_SkeletonAnimation_setAnimation00);
   tolua_function(tolua_S,"addAnimation",tolua_ExtensionsSpine_SkeletonAnimation_addAnimation00);
   tolua_function(tolua_S,"getCurrent",tolua_ExtensionsSpine_SkeletonAnimation_getCurrent00);
   tolua_function(tolua_S,"clearTracks",tolua_ExtensionsSpine_SkeletonAnimation_clearTracks00);
   tolua_function(tolua_S,"clearTrack",tolua_ExtensionsSpine_SkeletonAnimation_clearTrack00);
   tolua_function(tolua_S,"setStartListener",tolua_ExtensionsSpine_SkeletonAnimation_setStartListener00);
   tolua_function(tolua_S,"setEndListener",tolua_ExtensionsSpine_SkeletonAnimation_setEndListener00);
   tolua_function(tolua_S,"setCompleteListener",tolua_ExtensionsSpine_SkeletonAnimation_setCompleteListener00);
   tolua_function(tolua_S,"setEventListener",tolua_ExtensionsSpine_SkeletonAnimation_setEventListener00);
   tolua_function(tolua_S,"onAnimationStateEvent",tolua_ExtensionsSpine_SkeletonAnimation_onAnimationStateEvent00);
   tolua_function(tolua_S,"onTrackEntryEvent",tolua_ExtensionsSpine_SkeletonAnimation_onTrackEntryEvent00);
  tolua_endmodule(tolua_S);
 tolua_endmodule(tolua_S);
 return 1;
}


#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_ExtensionsSpine (lua_State* tolua_S) {
 return tolua_ExtensionsSpine_open(tolua_S);
};
#endif

