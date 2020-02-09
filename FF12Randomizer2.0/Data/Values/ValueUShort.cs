using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12RandomizerVer2
{
    public static class ValueUShort
    {
        public static ushort ReadUShort(this ByteArray data, int index)
        {
            return BitConverter.ToUInt16(data.Data, index);
        }

        public static void SetUShort(this ByteArray data, int index, ushort value)
        {
            data.SetSubArray(index, BitConverter.GetBytes(value));
        }
    }
}
