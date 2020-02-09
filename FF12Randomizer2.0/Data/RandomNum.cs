using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12RandomizerVer2
{
    class RandomNum
    {
        static Random rand = new Random();

        /// <summary>
        /// Gets a random number from (low, high)
        /// </summary>
        /// <param name="low"></param>
        /// <param name="high"></param>
        /// <returns></returns>
        public static int randInt(int low, int high)
        {
            return rand.Next(low, high + 1);
        }

        public static int randIntNorm(double center, double std, int low, int high)
        {
            double u1 = 1.0 - rand.NextDouble();
            double u2 = 1.0 - rand.NextDouble();
            double randStdNormal = Math.Sqrt(-2.0 * Math.Log(u1)) * Math.Sin(2.0 * Math.PI * u2);
            double randNormal = center + std * randStdNormal;
            return Math.Min(high, Math.Max(low, (int)Math.Round(randNormal)));
        }
    }
}
