using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FF12Randomizer
{
    public partial class Flag : UserControl
    {
        public event EventHandler OnChanged;

        public Flag()
        {
            InitializeComponent();
            checkBoxEnabled.CheckedChanged += OnChangedEvent;
        }

        public void setFlagData(Control flagData = null)
        {
            FlagData = flagData;
            if (FlagData != null)
            {
                FlagData.Dock = DockStyle.Fill;
                panel1.Controls.Add(FlagData);
            }
        }

        public string DescriptionFormat { get; set; } = "";
        public string Description
        {
            get
            {
                if (FlagData == null || !(FlagData is IFlagData))
                    return DescriptionFormat;
                return ((IFlagData)FlagData).getDescription(DescriptionFormat);
            }
        }

        public string FullDescriptionFormat { get; set; } = "";
        public string FullDescription
        {
            get
            {
                if (FullDescriptionFormat == "")
                    return Description;
                if (FlagData == null || !(FlagData is IFlagData))
                    return FullDescriptionFormat;
                return ((IFlagData)FlagData).getDescription(FullDescriptionFormat);
            }
        }
        [EditorBrowsable(EditorBrowsableState.Always)]
        [Browsable(true)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Visible)]
        [Bindable(true)]
        public override string Text
        {
            get => checkBoxEnabled.Text;
            set => checkBoxEnabled.Text = value;
        }

        public bool FlagEnabled
        {
            get => checkBoxEnabled.Checked;
            set => checkBoxEnabled.Checked = value;
        }

        public Control FlagData { get; set; }

        public static readonly Flag Empty = emptyFlag();

        private static Flag emptyFlag()
        {
            Flag flag = new Flag();
            flag.Text = "";
            return flag;
        }

        public void OnChangedEvent(object sender = null, EventArgs e = null)
        {
            labelDesc.Enabled = checkBoxEnabled.Checked;
            labelDesc.Text = Description;
            if (FlagData != null)
                FlagData.Enabled = checkBoxEnabled.Checked;
            if (OnChanged != null)
                OnChanged.Invoke(this, null);
        }
    }
}
