using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FF12Randomizer
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();

            tabControl1.SelectedIndexChanged += TabControl1_TabIndexChanged;

            TableLayoutPanel tableLayout = new TableLayoutPanel();
            tableLayout.Dock = DockStyle.Fill;
            tableLayout.ColumnCount = 1;
            tableLayout.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 100));
            tableLayout.CellBorderStyle = TableLayoutPanelCellBorderStyle.Single;
            tableLayout.AutoScroll = true;
            tabPageOpenWorld.Controls.Add(tableLayout);

            for (int i = 1; i <= 25; i++)
            {
                Flag flag = new Flag();
                flag.DescriptionFormat = "This is test description. Ex: This will set things to a value of ${Value}!";
                flag.FullDescriptionFormat = flag.DescriptionFormat + flag.DescriptionFormat + flag.DescriptionFormat + flag.DescriptionFormat;
                flag.setFlagData(new FlagValue(flag));

                flag.Text = $"Really Long Flag Name for Flag {i}";
                addFlagEvents(flag);
                flag.Dock = DockStyle.Fill;
                
                flag.OnChangedEvent();
                flag.OnChanged += Flag_OnChanged;

                tableLayout.Controls.Add(flag);

            }
        }

        private void TabControl1_TabIndexChanged(object sender, EventArgs e)
        {
            flagInfo1.Flag = Flag.Empty;
        }

        private void Flag_OnChanged(object sender, EventArgs e)
        {
            Control control = (Control)sender;
            while (!(control is Flag))
            {
                control = control.Parent;
            }
            if (flagInfo1.Flag == (Flag)control)
                flagInfo1.Update();
        }

        private void addFlagEvents(Control control)
        {
            control.MouseEnter += Flag_MouseEnter;
            control.MouseLeave += Flag_MouseLeave;
            foreach (Control cont in control.Controls)
            {
                addFlagEvents(cont);
            }
        }

        private void Flag_MouseLeave(object sender, EventArgs e)
        {
        }

        private void Flag_MouseEnter(object sender, EventArgs e)
        {
            Control control = (Control)sender;
            while (!(control is Flag))
            {
                control = control.Parent;
            }
            flagInfo1.Flag = (Flag)control;
        }

        private void tabControl1_DrawItem(object sender, DrawItemEventArgs e)
        {
            Graphics g = e.Graphics;
            Brush _textBrush;

            // Get the item from the collection.
            TabPage _tabPage = tabControl1.TabPages[e.Index];

            // Get the real bounds for the tab rectangle.
            Rectangle _tabBounds = tabControl1.GetTabRect(e.Index);

            if (e.State == DrawItemState.Selected)
            {

                // Draw a different background color, and don't paint a focus rectangle.
                _textBrush = new SolidBrush(e.ForeColor);
                g.FillRectangle(Brushes.Gray, e.Bounds);
            }
            else
            {
                _textBrush = new System.Drawing.SolidBrush(e.ForeColor);
                //g.FillRectangle(Brushes.LightGray, e.Bounds);
            }

            // Use our own font.
            Font _tabFont = e.Font;

            // Draw string. Center the text.
            StringFormat _stringFlags = new StringFormat();
            _stringFlags.Alignment = StringAlignment.Center;
            _stringFlags.LineAlignment = StringAlignment.Center;
            g.DrawString(_tabPage.Text, _tabFont, _textBrush, _tabBounds, new StringFormat(_stringFlags));
        }
    }
}
