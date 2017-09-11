#include "MrbRect.hpp"

#include "Util.hpp"

//----------------------------------------------------------
namespace siv3druby {
MrbObject<Rect>::Inner MrbRect::fInner;

//----------------------------------------------------------
void MrbRect::Init(mrb_state* mrb)
{
    MrbObject::Init(mrb, "Rect");

    mrb_define_method(mrb, Cc(), "initialize", initialize, MRB_ARGS_REQ(4));
    mrb_define_method(mrb, Cc(), "draw", draw, MRB_ARGS_OPT(1));
}

//----------------------------------------------------------
mrb_value MrbRect::initialize(mrb_state *mrb, mrb_value self)
{
    mrb_float x, y, w, h;
    mrb_get_args(mrb, "ffff", &x, &y, &w, &h);

    auto* obj = new Rect(x, y, w, h);

    mrb_data_init(self, obj, DataType());
    return self;
}

//----------------------------------------------------------
mrb_value MrbRect::draw(mrb_state *mrb, mrb_value self)
{
    mrb_value color;
    int argc = mrb_get_args(mrb, "|o", &color);

    switch (argc)
    {
        case 1:
            Self(self).draw(Util::ToColor(mrb, color));
            break;
        default:
            Self(self).draw();
            break;
    }

    return mrb_nil_value();
}

}
