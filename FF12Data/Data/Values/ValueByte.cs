﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12Data
{
    public static class ValueByte
    {
        public static byte ReadByte(this ByteArray data, int index)
        {
            return data.Data[index];
        }

        public static void SetByte(this ByteArray data, int index, byte value)
        {
            data.SetSubArray(index,new byte[] { value });
        }
    }
}
