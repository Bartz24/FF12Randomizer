using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12Randomizer
{
    public abstract class Flag
    {
        public bool Enabled { get; set; }
        public string Name { get; set; }

        public static readonly Flag EMPTY = new SimpleFlag();
    }
}
