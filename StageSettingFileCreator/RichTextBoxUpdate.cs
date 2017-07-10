using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StageSettingFileCreator
{
    partial class Form1
    {
        private DateTime StatutoryPaymentDeadlineOfIncomeTax()
        {
            DateTime StatutoryPaymentDeadline = new DateTime(int.Parse(TaxYear.Text) + 1, 3, 15);
            return DayOfWeek.Saturday == StatutoryPaymentDeadline.DayOfWeek
                    ? StatutoryPaymentDeadline.AddDays(2)
                    : DayOfWeek.Sunday == StatutoryPaymentDeadline.DayOfWeek
                        ? StatutoryPaymentDeadline.AddDays(1)
                        : StatutoryPaymentDeadline
                    ;
        }
        private string PrintInfoInRichTextBoxOfIncomeTax()
        {
            return "本税の合計：\\" + TaxTotal.Text
                + "\n追徴課税額：\\" + (int.Parse(TaxTotal.Text) - int.Parse(AlreadyPaid.Text)).ToString()
                + "\n延滞税：\\" + new DelayTax(StatutoryPaymentDeadlineOfIncomeTax()).Calc(
                        int.Parse(TaxTotal.Text),
                        new DateTime(
                            int.Parse(ForcedInvestigationYear.Text),
                            int.Parse(ForceInvestigationMonth.Text),
                            int.Parse(ForceInvestigationDay.Text)
                        ).AddDays(7)
                    ).ToString()
                + GetAdditionalTax()
                + "\n強制調査実施：" + GetRevenue(comboBox1.Text) + "査察部\n"
                + "嫌疑者名：" + textBox2.Text;
        }
        private string PrintInfoInRichTextBoxOfCorporateTax()
        {

        }
        private string PrintInfoInRichTextBoxOfInheritanceTax()
        {

        }
        private string PrintInfoInRichTextBoxOfCorporateConsumptionTax()
        {

        }
        private string PrintInfoInRichTextBoxOfIndividualBusinessConsumption()
        {

        }
        private string GetAdditionalTax()
        {
            AdditionalTax Add = new AdditionalTax(int.Parse(TaxTotal.Text), int.Parse(AlreadyPaid.Text));
            if (!checkBox2.Checked) return "重加算税：\\" + Add.Heavy(checkBox1.Checked);
            else if (!checkBox1.Checked) return "無申告加算税：\\" + Add.Undeclared();
            else if (0 == int.Parse(AlreadyPaid.Text)) return "不納付加算税：\\" + Add.NoPayment();
            else return "過少申告加算税：\\" + Add.UnderReporting();
        }
        private string[] JurisdictionOfSendaiRevenue = { "青森県", "秋田県", "岩手県", "山形県", "宮城県", "福島県" };
        private string[] JurisdictionOfKantoShinetsuRevenue = { "新潟県", "長野県", "群馬県", "栃木県", "茨城県", "埼玉県" };
        private string[] JurisdictionOfTokyoRevenue = { "東京都", "神奈川県", "千葉県", "山梨県" };
        private string[] JurisdictionOfKanazawaRevenue = { "富山県", "石川県", "福井県" };
        private string[] JurisdictionOfNagoyaRevenue = { "静岡県", "愛知県", "岐阜県", "三重県" };
        private string[] JurisdictionOfOsakaRevenue = { "滋賀県", "京都府", "大阪府", "奈良県", "和歌山県", "兵庫県" };
        private string[] JurisdictionOfHiroshimaRevenue = { "鳥取県", "島根県", "岡山県", "広島県", "山口県" };
        private string[] JurisdictionOfTakamatsuRevenue = { "香川県", "愛媛県", "徳島県", "高知県" };
        private string[] JurisdictionOfFukuokaRevenue = { "福岡県", "佐賀県", "長崎県" };
        private string[] JurisdictionOfKumamotoRevenue = { "大分県", "熊本県", "宮崎県", "鹿児島県" };
        private string GetRevenue(string Prefectures)
        {
            if (Prefectures.Equals("北海道")) return "札幌国税局";
            else if (Prefectures.Equals("沖縄県")) return "沖縄国税事務所";
            for (int i = 0; i < JurisdictionOfSendaiRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "仙台国税局";
            for (int i = 0; i < JurisdictionOfKantoShinetsuRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "関東信越国税局";
            for (int i = 0; i < JurisdictionOfTokyoRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "東京国税局";
            for (int i = 0; i < JurisdictionOfKanazawaRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "金沢国税局";
            for (int i = 0; i < JurisdictionOfNagoyaRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "名古屋国税局";
            for (int i = 0; i < JurisdictionOfOsakaRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "大阪国税局";
            for (int i = 0; i < JurisdictionOfHiroshimaRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "広島国税局";
            for (int i = 0; i < JurisdictionOfTakamatsuRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "高松国税局";
            for (int i = 0; i < JurisdictionOfFukuokaRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "福岡国税局";
            for (int i = 0; i < JurisdictionOfKumamotoRevenue.Length; i++) if (Prefectures == JurisdictionOfSendaiRevenue[i]) return "熊本国税局";
            return "";
        }
    }
}
