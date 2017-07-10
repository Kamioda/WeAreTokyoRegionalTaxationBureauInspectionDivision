using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace StageSettingFileCreator
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }
        private void IncomeTaxRichTextBoxUpdate()
        {
                try
                {
                    IncomeTaxRichTextBox.Text = PrintInfoInRichTextBoxOfIncomeTax();
                }
                catch (Exception)
                {
                    IncomeTaxRichTextBox.Text = "必須項目が全て入力されていません。";
                }
        }
        private void CorporateTaxRichTextBoxUpdate()
        {
            try
            {
                CorporateTaxRichTextBox.Text = PrintInfoInRichTextBoxOfCorporateTax();
            }
            catch (Exception)
            {
                CorporateTaxRichTextBox.Text = "必須項目が全て入力されていません。";
            }
        }
        public override void Refresh()
        {
            IncomeTaxRichTextBoxUpdate();
            CorporateTaxRichTextBoxUpdate();
            base.Refresh();
        }
        private void textBoxKeyPress(object sender, KeyPressEventArgs e)
        {
            if (e.KeyChar < '0' || e.KeyChar > '9') e.Handled = true;
        }
    }
}
