#pragma once

#include <Siv3D.hpp>
#include "MrbObject.hpp"
#include "mruby.h"
#include "mruby/class.h"
#include "mruby/data.h"

//----------------------------------------------------------
namespace siv3druby {

//----------------------------------------------------------

template <class T>
class MrbTextureObject
    : public MrbObject<T>
{
public:
    static void Init(mrb_state *mrb, std::string name)
    {
        MrbObject::Init(mrb, name);

        mrb_define_method(mrb, Cc(), "flip", flip, MRB_ARGS_NONE());
        mrb_define_method(mrb, Cc(), "mirror", mirror, MRB_ARGS_NONE());
        mrb_define_method(mrb, Cc(), "scale", scale, MRB_ARGS_ARG(1, 1));
        mrb_define_method(mrb, Cc(), "resize", resize, MRB_ARGS_REQ(2));
    }

private:
    //----------------------------------------------------------
    static mrb_value flip(mrb_state *mrb, mrb_value self)
    {
        return MrbTextureRegion::ToMrb(
            mrb,
            new TextureRegion(Self(self).flip())
            );
    }

    //----------------------------------------------------------
    static mrb_value mirror(mrb_state *mrb, mrb_value self)
    {
        return MrbTextureRegion::ToMrb(
            mrb,
            new TextureRegion(Self(self).mirror())
            );
    }

    //----------------------------------------------------------
    static mrb_value resize(mrb_state *mrb, mrb_value self)
    {
        mrb_float x, y;
        int argc = mrb_get_args(mrb, "ff", &x, &y);

        return MrbTextureRegion::ToMrb(
            mrb,
            new TextureRegion(Self(self).resize(x, y))
            );
    }

    //----------------------------------------------------------
    static mrb_value scale(mrb_state *mrb, mrb_value self)
    {
        mrb_float x, y;
        int argc = mrb_get_args(mrb, "f|f", &x, &y);

        switch (argc)
        {
            case 2:
                return MrbTextureRegion::ToMrb(
                    mrb,
                    new TextureRegion(Self(self).scale(x, y))
                    );
            default:
                return MrbTextureRegion::ToMrb(
                    mrb,
                    new TextureRegion(Self(self).scale(x))
                    );
        }
    }
};
}
