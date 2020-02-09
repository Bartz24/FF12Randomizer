using PropertyChanged;
using System;
using System.Collections.Generic;
using System.Collections.ObjectModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace FF12RandomizerVer2
{
    [AddINotifyPropertyChangedInterface]
    public class MainViewModel
    {
        public ObservableCollection<Flag> Items { get; set; }

        private Flag currentFlag;

        public Flag CurrentFlag
        {
            get
            {
                if (currentFlag == null)
                    return Flag.EMPTY;
                return currentFlag;
            }
            set
            {
                currentFlag = value;
            }
        }

        public MainViewModel()
        {
            Items = new ObservableCollection<Flag>
            {
                new SimpleFlag
                {
                    Name = "Test 1."
                },
                new ValueFlag
                {
                    Name = "Test 2!",
                    Value = 75,
                    MinValue=0,
                    MaxValue=100
                }
            };
        }
    }
}
