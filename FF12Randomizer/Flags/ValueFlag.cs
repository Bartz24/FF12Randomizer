using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12Randomizer
{
    public class ValueFlag : Flag
    {
        public int MinValue { get; set; }
        public int MaxValue { get; set; }
        public int Value { get; set; }

        public string DisplayValue
        {
            get
            {
                return $"{Value}%";
            }
        }
    }
}
