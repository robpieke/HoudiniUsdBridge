/*
 * PROPRIETARY INFORMATION.  This software is proprietary to
 * Side Effects Software Inc., and is not to be reproduced,
 * transmitted, or disclosed in any way without written permission.
 *
 * NAME:	BRAY_HdVolume.h (BRAY Library, C++)
 *
 * COMMENTS:
 */

#ifndef __BRAY_HD_VOLUME_H__
#define __BRAY_HD_VOLUME_H__

#include <BRAY/BRAY_Interface.h>
#include <pxr/imaging/hd/volume.h>

PXR_NAMESPACE_OPEN_SCOPE

class BRAY_HdParam;

class BRAY_HdVolume : public HdVolume
{
public:
    BRAY_HdVolume(const SdfPath& id,
	const SdfPath& instancerId = SdfPath());

    virtual ~BRAY_HdVolume() = default;

    /// Release any resources this class is holding onto - in this case,
    /// destroy the geometry object in the scene graph.
    virtual void	Finalize(HdRenderParam *renderParam) override final;

    /// Pull invalidated scene data and prepare/update the renderable
    /// representation.
    virtual void	Sync(HdSceneDelegate *sceneDelegate,
			    HdRenderParam *renerParam,
			    HdDirtyBits *dirtyBits,
			    TfToken const &repr) override final;

    /// Inform the scene graph which state needs to be downloaded in the first
    /// Sync() call.  In this case, topology and point data.
    virtual HdDirtyBits	GetInitialDirtyBitsMask() const override final;

protected:
    /// This callback gives the prim an opportunity to set additional dirty
    /// bits based on those already set.
    virtual HdDirtyBits	_PropagateDirtyBits(HdDirtyBits bits)
	const override final;

    /// Initialize the given representation of the prim
    virtual void	_InitRepr(TfToken const &repr,
	HdDirtyBits *dirtyBits) override final;

private:
    void		updateGTVolume(BRAY_HdParam &rparm,
			    HdSceneDelegate *sceneDelegate,
			    HdDirtyBits *dirtyBits);

    BRAY::ObjectPtr	    myInstance;
    BRAY::ObjectPtr	    myVolume;
    UT_Array<GfMatrix4d>    myXform;
};

PXR_NAMESPACE_CLOSE_SCOPE

#endif
