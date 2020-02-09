using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12Data
{
    public static class Extensions
    {
        public static T[] SubArray<T>(this T[] data, int index, int length)
        {
            T[] result = new T[length];
            Array.Copy(data, index, result, 0, length);
            return result;
        }

        public static void SetSubArray<T>(this T[] data, int index, T[] subArray)
        {
            for (int i = 0; i < subArray.Length; i++)
                data[index + i] = subArray[i];
        }
    }
}
