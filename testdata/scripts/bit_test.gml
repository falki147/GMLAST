#define bit_test
/// bit_test(bitfield,bit)
//
//  Returns the state of a bit within a given bitfield.
//
//      bitfield    number or group of bits, integer
//      bit         bit index to test, integer
//
/// GMLscripts.com/license
{
    return 1 & (argument0 >> argument1);
}