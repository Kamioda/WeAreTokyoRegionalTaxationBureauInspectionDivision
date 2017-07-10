using System;
using System.Windows.Forms;

namespace StageSettingFileCreator
{
    partial class Form1
    {
        /// <summary>
        /// 必要なデザイナー変数です。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 使用中のリソースをすべてクリーンアップします。
        /// </summary>
        /// <param name="disposing">マネージ リソースを破棄する場合は true を指定し、その他の場合は false を指定します。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows フォーム デザイナーで生成されたコード

        /// <summary>
        /// デザイナー サポートに必要なメソッドです。このメソッドの内容を
        /// コード エディターで変更しないでください。
        /// </summary>
        private void InitializeComponent()
        {
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.IncomeTax = new System.Windows.Forms.TabPage();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this.label14 = new System.Windows.Forms.Label();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.label13 = new System.Windows.Forms.Label();
            this.IncomeTaxRichTextBox = new System.Windows.Forms.RichTextBox();
            this.checkBox2 = new System.Windows.Forms.CheckBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.label10 = new System.Windows.Forms.Label();
            this.ForceInvestigationDay = new System.Windows.Forms.TextBox();
            this.label9 = new System.Windows.Forms.Label();
            this.ForceInvestigationMonth = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.ForcedInvestigationYear = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.AlreadyPaid = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.TaxTotal = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.TaxYear = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.CorporateTax = new System.Windows.Forms.TabPage();
            this.label12 = new System.Windows.Forms.Label();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label11 = new System.Windows.Forms.Label();
            this.CorporateTaxRichTextBox = new System.Windows.Forms.RichTextBox();
            this.InheritanceTax = new System.Windows.Forms.TabPage();
            this.InheritanceTaxRichTextBox = new System.Windows.Forms.RichTextBox();
            this.CorporateConsumptionTax = new System.Windows.Forms.TabPage();
            this.CorporateConsumptionTaxRichTextBox = new System.Windows.Forms.RichTextBox();
            this.IndividualBusinessConsumptionTax = new System.Windows.Forms.TabPage();
            this.IndividualBusinessConsumptionTaxRichTextBox = new System.Windows.Forms.RichTextBox();
            this.tabControl1.SuspendLayout();
            this.IncomeTax.SuspendLayout();
            this.CorporateTax.SuspendLayout();
            this.InheritanceTax.SuspendLayout();
            this.CorporateConsumptionTax.SuspendLayout();
            this.IndividualBusinessConsumptionTax.SuspendLayout();
            this.SuspendLayout();
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.IncomeTax);
            this.tabControl1.Controls.Add(this.CorporateTax);
            this.tabControl1.Controls.Add(this.InheritanceTax);
            this.tabControl1.Controls.Add(this.CorporateConsumptionTax);
            this.tabControl1.Controls.Add(this.IndividualBusinessConsumptionTax);
            this.tabControl1.Location = new System.Drawing.Point(13, 13);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(615, 335);
            this.tabControl1.TabIndex = 0;
            // 
            // IncomeTax
            // 
            this.IncomeTax.Controls.Add(this.comboBox1);
            this.IncomeTax.Controls.Add(this.label14);
            this.IncomeTax.Controls.Add(this.textBox2);
            this.IncomeTax.Controls.Add(this.label13);
            this.IncomeTax.Controls.Add(this.IncomeTaxRichTextBox);
            this.IncomeTax.Controls.Add(this.checkBox2);
            this.IncomeTax.Controls.Add(this.checkBox1);
            this.IncomeTax.Controls.Add(this.label10);
            this.IncomeTax.Controls.Add(this.ForceInvestigationDay);
            this.IncomeTax.Controls.Add(this.label9);
            this.IncomeTax.Controls.Add(this.ForceInvestigationMonth);
            this.IncomeTax.Controls.Add(this.label8);
            this.IncomeTax.Controls.Add(this.ForcedInvestigationYear);
            this.IncomeTax.Controls.Add(this.label7);
            this.IncomeTax.Controls.Add(this.label6);
            this.IncomeTax.Controls.Add(this.label5);
            this.IncomeTax.Controls.Add(this.label4);
            this.IncomeTax.Controls.Add(this.AlreadyPaid);
            this.IncomeTax.Controls.Add(this.label3);
            this.IncomeTax.Controls.Add(this.TaxTotal);
            this.IncomeTax.Controls.Add(this.label2);
            this.IncomeTax.Controls.Add(this.TaxYear);
            this.IncomeTax.Controls.Add(this.label1);
            this.IncomeTax.Font = new System.Drawing.Font("ＭＳ ゴシック", 11F);
            this.IncomeTax.Location = new System.Drawing.Point(4, 22);
            this.IncomeTax.Name = "IncomeTax";
            this.IncomeTax.Padding = new System.Windows.Forms.Padding(3);
            this.IncomeTax.Size = new System.Drawing.Size(607, 309);
            this.IncomeTax.TabIndex = 0;
            this.IncomeTax.Text = "所得税";
            this.IncomeTax.UseVisualStyleBackColor = true;
            // 
            // comboBox1
            // 
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Items.AddRange(new object[] {
            "北海道",
            "青森県",
            "秋田県",
            "岩手県",
            "山形県",
            "宮城県",
            "福島県",
            "新潟県",
            "長野県",
            "群馬県",
            "栃木県",
            "茨城県",
            "埼玉県",
            "東京都",
            "神奈川県",
            "千葉県",
            "山梨県",
            "富山県",
            "石川県",
            "福井県",
            "静岡県",
            "愛知県",
            "岐阜県",
            "三重県",
            "滋賀県",
            "京都府",
            "大阪府",
            "奈良県",
            "和歌山県",
            "兵庫県",
            "鳥取県",
            "島根県",
            "岡山県",
            "広島県",
            "山口県",
            "香川県",
            "愛媛県",
            "徳島県",
            "高知県",
            "福岡県",
            "佐賀県",
            "長崎県",
            "大分県",
            "熊本県",
            "宮崎県",
            "鹿児島県",
            "沖縄県"});
            this.comboBox1.Location = new System.Drawing.Point(116, 214);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(149, 23);
            this.comboBox1.TabIndex = 27;
            // 
            // label14
            // 
            this.label14.AutoSize = true;
            this.label14.Location = new System.Drawing.Point(7, 217);
            this.label14.Name = "label14";
            this.label14.Size = new System.Drawing.Size(103, 15);
            this.label14.TabIndex = 26;
            this.label14.Text = "嫌疑者の住所";
            // 
            // textBox2
            // 
            this.textBox2.Location = new System.Drawing.Point(116, 192);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(149, 22);
            this.textBox2.TabIndex = 25;
            // 
            // label13
            // 
            this.label13.AutoSize = true;
            this.label13.Location = new System.Drawing.Point(7, 195);
            this.label13.Name = "label13";
            this.label13.Size = new System.Drawing.Size(103, 15);
            this.label13.TabIndex = 24;
            this.label13.Text = "嫌疑者の名前";
            // 
            // IncomeTaxRichTextBox
            // 
            this.IncomeTaxRichTextBox.Location = new System.Drawing.Point(307, 7);
            this.IncomeTaxRichTextBox.Name = "IncomeTaxRichTextBox";
            this.IncomeTaxRichTextBox.ReadOnly = true;
            this.IncomeTaxRichTextBox.Size = new System.Drawing.Size(294, 296);
            this.IncomeTaxRichTextBox.TabIndex = 23;
            this.IncomeTaxRichTextBox.Text = "";
            // 
            // checkBox2
            // 
            this.checkBox2.AutoSize = true;
            this.checkBox2.Location = new System.Drawing.Point(10, 168);
            this.checkBox2.Name = "checkBox2";
            this.checkBox2.Size = new System.Drawing.Size(234, 19);
            this.checkBox2.TabIndex = 22;
            this.checkBox2.Text = "過失によって脱税と疑われた";
            this.checkBox2.UseVisualStyleBackColor = true;
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.Location = new System.Drawing.Point(10, 142);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(170, 19);
            this.checkBox1.TabIndex = 21;
            this.checkBox1.Text = "確定申告していない";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(226, 117);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(23, 15);
            this.label10.TabIndex = 16;
            this.label10.Text = "日";
            // 
            // ForceInvestigationDay
            // 
            this.ForceInvestigationDay.Location = new System.Drawing.Point(170, 114);
            this.ForceInvestigationDay.Name = "ForceInvestigationDay";
            this.ForceInvestigationDay.Size = new System.Drawing.Size(50, 22);
            this.ForceInvestigationDay.TabIndex = 15;
            this.ForceInvestigationDay.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(226, 95);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(23, 15);
            this.label9.TabIndex = 14;
            this.label9.Text = "月";
            // 
            // ForceInvestigationMonth
            // 
            this.ForceInvestigationMonth.Location = new System.Drawing.Point(170, 92);
            this.ForceInvestigationMonth.Name = "ForceInvestigationMonth";
            this.ForceInvestigationMonth.Size = new System.Drawing.Size(50, 22);
            this.ForceInvestigationMonth.TabIndex = 13;
            this.ForceInvestigationMonth.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(226, 73);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(23, 15);
            this.label8.TabIndex = 11;
            this.label8.Text = "年";
            // 
            // ForcedInvestigationYear
            // 
            this.ForcedInvestigationYear.Location = new System.Drawing.Point(170, 70);
            this.ForcedInvestigationYear.Name = "ForcedInvestigationYear";
            this.ForcedInvestigationYear.Size = new System.Drawing.Size(50, 22);
            this.ForcedInvestigationYear.TabIndex = 10;
            this.ForcedInvestigationYear.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(7, 73);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(103, 15);
            this.label7.TabIndex = 9;
            this.label7.Text = "強制調査実施";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(226, 7);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(39, 15);
            this.label6.TabIndex = 8;
            this.label6.Text = "年度";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(226, 51);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(39, 15);
            this.label5.TabIndex = 7;
            this.label5.Text = "千円";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(226, 29);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(39, 15);
            this.label4.TabIndex = 6;
            this.label4.Text = "千円";
            // 
            // AlreadyPaid
            // 
            this.AlreadyPaid.Location = new System.Drawing.Point(120, 48);
            this.AlreadyPaid.Name = "AlreadyPaid";
            this.AlreadyPaid.Size = new System.Drawing.Size(100, 22);
            this.AlreadyPaid.TabIndex = 5;
            this.AlreadyPaid.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(7, 51);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(103, 15);
            this.label3.TabIndex = 4;
            this.label3.Text = "期限内納付額";
            // 
            // TaxTotal
            // 
            this.TaxTotal.Location = new System.Drawing.Point(120, 26);
            this.TaxTotal.Name = "TaxTotal";
            this.TaxTotal.Size = new System.Drawing.Size(100, 22);
            this.TaxTotal.TabIndex = 3;
            this.TaxTotal.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(7, 29);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(87, 15);
            this.label2.TabIndex = 2;
            this.label2.Text = "本税の合計";
            // 
            // TaxYear
            // 
            this.TaxYear.Font = new System.Drawing.Font("ＭＳ ゴシック", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.TaxYear.Location = new System.Drawing.Point(170, 4);
            this.TaxYear.Name = "TaxYear";
            this.TaxYear.Size = new System.Drawing.Size(50, 22);
            this.TaxYear.TabIndex = 1;
            this.TaxYear.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.textBoxKeyPress);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("MS UI Gothic", 11F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label1.Location = new System.Drawing.Point(7, 7);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(92, 15);
            this.label1.TabIndex = 0;
            this.label1.Text = "課税年(西暦)";
            // 
            // CorporateTax
            // 
            this.CorporateTax.Controls.Add(this.label12);
            this.CorporateTax.Controls.Add(this.textBox1);
            this.CorporateTax.Controls.Add(this.label11);
            this.CorporateTax.Controls.Add(this.CorporateTaxRichTextBox);
            this.CorporateTax.Location = new System.Drawing.Point(4, 22);
            this.CorporateTax.Name = "CorporateTax";
            this.CorporateTax.Padding = new System.Windows.Forms.Padding(3);
            this.CorporateTax.Size = new System.Drawing.Size(607, 309);
            this.CorporateTax.TabIndex = 1;
            this.CorporateTax.Text = "法人税";
            this.CorporateTax.UseVisualStyleBackColor = true;
            // 
            // label12
            // 
            this.label12.AutoSize = true;
            this.label12.Font = new System.Drawing.Font("ＭＳ ゴシック", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label12.Location = new System.Drawing.Point(63, 26);
            this.label12.Name = "label12";
            this.label12.Size = new System.Drawing.Size(23, 15);
            this.label12.TabIndex = 27;
            this.label12.Text = "年";
            // 
            // textBox1
            // 
            this.textBox1.Font = new System.Drawing.Font("ＭＳ ゴシック", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.textBox1.Location = new System.Drawing.Point(7, 26);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(50, 22);
            this.textBox1.TabIndex = 26;
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Font = new System.Drawing.Font("ＭＳ ゴシック", 11.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(128)));
            this.label11.Location = new System.Drawing.Point(7, 7);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(119, 15);
            this.label11.TabIndex = 25;
            this.label11.Text = "課税期間(終了)";
            // 
            // CorporateTaxRichTextBox
            // 
            this.CorporateTaxRichTextBox.Location = new System.Drawing.Point(307, 7);
            this.CorporateTaxRichTextBox.Name = "CorporateTaxRichTextBox";
            this.CorporateTaxRichTextBox.ReadOnly = true;
            this.CorporateTaxRichTextBox.Size = new System.Drawing.Size(294, 296);
            this.CorporateTaxRichTextBox.TabIndex = 24;
            this.CorporateTaxRichTextBox.Text = "";
            // 
            // InheritanceTax
            // 
            this.InheritanceTax.Controls.Add(this.InheritanceTaxRichTextBox);
            this.InheritanceTax.Location = new System.Drawing.Point(4, 22);
            this.InheritanceTax.Name = "InheritanceTax";
            this.InheritanceTax.Padding = new System.Windows.Forms.Padding(3);
            this.InheritanceTax.Size = new System.Drawing.Size(607, 309);
            this.InheritanceTax.TabIndex = 2;
            this.InheritanceTax.Text = "相続税";
            this.InheritanceTax.UseVisualStyleBackColor = true;
            // 
            // InheritanceTaxRichTextBox
            // 
            this.InheritanceTaxRichTextBox.Location = new System.Drawing.Point(307, 6);
            this.InheritanceTaxRichTextBox.Name = "InheritanceTaxRichTextBox";
            this.InheritanceTaxRichTextBox.ReadOnly = true;
            this.InheritanceTaxRichTextBox.Size = new System.Drawing.Size(294, 296);
            this.InheritanceTaxRichTextBox.TabIndex = 24;
            this.InheritanceTaxRichTextBox.Text = "";
            // 
            // CorporateConsumptionTax
            // 
            this.CorporateConsumptionTax.Controls.Add(this.CorporateConsumptionTaxRichTextBox);
            this.CorporateConsumptionTax.Location = new System.Drawing.Point(4, 22);
            this.CorporateConsumptionTax.Name = "CorporateConsumptionTax";
            this.CorporateConsumptionTax.Padding = new System.Windows.Forms.Padding(3);
            this.CorporateConsumptionTax.Size = new System.Drawing.Size(607, 309);
            this.CorporateConsumptionTax.TabIndex = 3;
            this.CorporateConsumptionTax.Text = "法人消費税";
            this.CorporateConsumptionTax.UseVisualStyleBackColor = true;
            // 
            // CorporateConsumptionTaxRichTextBox
            // 
            this.CorporateConsumptionTaxRichTextBox.Location = new System.Drawing.Point(307, 6);
            this.CorporateConsumptionTaxRichTextBox.Name = "CorporateConsumptionTaxRichTextBox";
            this.CorporateConsumptionTaxRichTextBox.ReadOnly = true;
            this.CorporateConsumptionTaxRichTextBox.Size = new System.Drawing.Size(294, 296);
            this.CorporateConsumptionTaxRichTextBox.TabIndex = 24;
            this.CorporateConsumptionTaxRichTextBox.Text = "";
            // 
            // IndividualBusinessConsumptionTax
            // 
            this.IndividualBusinessConsumptionTax.Controls.Add(this.IndividualBusinessConsumptionTaxRichTextBox);
            this.IndividualBusinessConsumptionTax.Location = new System.Drawing.Point(4, 22);
            this.IndividualBusinessConsumptionTax.Name = "IndividualBusinessConsumptionTax";
            this.IndividualBusinessConsumptionTax.Padding = new System.Windows.Forms.Padding(3);
            this.IndividualBusinessConsumptionTax.Size = new System.Drawing.Size(607, 309);
            this.IndividualBusinessConsumptionTax.TabIndex = 4;
            this.IndividualBusinessConsumptionTax.Text = "個人事業消費税";
            this.IndividualBusinessConsumptionTax.UseVisualStyleBackColor = true;
            // 
            // IndividualBusinessConsumptionTaxRichTextBox
            // 
            this.IndividualBusinessConsumptionTaxRichTextBox.Location = new System.Drawing.Point(307, 6);
            this.IndividualBusinessConsumptionTaxRichTextBox.Name = "IndividualBusinessConsumptionTaxRichTextBox";
            this.IndividualBusinessConsumptionTaxRichTextBox.ReadOnly = true;
            this.IndividualBusinessConsumptionTaxRichTextBox.Size = new System.Drawing.Size(294, 296);
            this.IndividualBusinessConsumptionTaxRichTextBox.TabIndex = 24;
            this.IndividualBusinessConsumptionTaxRichTextBox.Text = "";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(640, 360);
            this.Controls.Add(this.tabControl1);
            this.Name = "Form1";
            this.Text = "東京国税局査察部です　ステージ設定ファイルクリエイター";
            this.tabControl1.ResumeLayout(false);
            this.IncomeTax.ResumeLayout(false);
            this.IncomeTax.PerformLayout();
            this.CorporateTax.ResumeLayout(false);
            this.CorporateTax.PerformLayout();
            this.InheritanceTax.ResumeLayout(false);
            this.CorporateConsumptionTax.ResumeLayout(false);
            this.IndividualBusinessConsumptionTax.ResumeLayout(false);
            this.ResumeLayout(false);

        }
        #endregion

        private TabControl tabControl1;
        private TabPage IncomeTax;
        private TabPage CorporateTax;
        private TabPage InheritanceTax;
        private TabPage CorporateConsumptionTax;
        private Label label1;
        private TextBox TaxYear;
        private Label label10;
        private TextBox ForceInvestigationDay;
        private Label label9;
        private TextBox ForceInvestigationMonth;
        private Label label8;
        private TextBox ForcedInvestigationYear;
        private Label label7;
        private Label label6;
        private Label label5;
        private Label label4;
        private TextBox AlreadyPaid;
        private Label label3;
        private TextBox TaxTotal;
        private Label label2;
        private CheckBox checkBox2;
        private CheckBox checkBox1;
        private RichTextBox IncomeTaxRichTextBox;
        private Label label12;
        private TextBox textBox1;
        private Label label11;
        private RichTextBox CorporateTaxRichTextBox;
        private RichTextBox InheritanceTaxRichTextBox;
        private RichTextBox CorporateConsumptionTaxRichTextBox;
        private TabPage IndividualBusinessConsumptionTax;
        private RichTextBox IndividualBusinessConsumptionTaxRichTextBox;
        private ComboBox comboBox1;
        private Label label14;
        private TextBox textBox2;
        private Label label13;
    }
}

