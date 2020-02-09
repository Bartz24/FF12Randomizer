using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12RandomizerVer2
{
    [Flags]
    public enum Element
    {
        NonElemental = 0x00,
        Fire = 0x01,
        Ice = 0x02,
        Thunder = 0x04,
        Earth = 0x08,
        Poison = 0x10,
        Wind = 0x20,
        Water = 0x40,
        Holy = 0x80
    }
}
