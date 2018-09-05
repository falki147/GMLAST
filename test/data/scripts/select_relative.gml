#define select_relative
/// select_relative(current,delta,choice1,choice2...)
//
//  Returns an argument in a position relative to a given value.
//  If a relative position is beyond the range of given choices,
//  the position is clamped to be within range. If current value
//  isn't among the choices, the return value is undefined.
//
//      current     value matching a given choice
//      delta       relative position of desired choice, integer
//      choiceN     value to return, if selected
//
//  eg. select_relative("Name", -2, "Hello", "Doctor", "Name") == "Hello"
//      select_relative("Doctor", 2, "Hello", "Doctor", "Name") == "Name"
//
/// GMLscripts.com/license
{
    var current = argument[0];
    var delta = argument[1];
    var size = argument_count - 2;
    var choices = ds_list_create();
    for (var i = 2; i < argument_count; i++) ds_list_add(choices, argument[i]);
    i = ds_list_find_index(choices, current);
    if (i < 0) return undefined;
    i = clamp(i + delta, 0, size - 1);
    var result = ds_list_find_value(choices, i);
    ds_list_destroy(choices);
    return result;
}