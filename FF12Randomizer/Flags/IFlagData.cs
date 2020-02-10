using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FF12Randomizer
{
    interface IFlagData
    {
        FormattingMap GetFormattingMap();
        string getDescription(string format);
        Flag getParentFlag();
        UserControl getFlagInfo();
    }
}
