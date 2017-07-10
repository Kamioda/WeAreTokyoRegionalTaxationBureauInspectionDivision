using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace StageSettingFileCreator
{
    /// <summary>
    /// 延滞税
    /// </summary>
    class DelayTax
    {
        /// <summary>
        /// 法定納付期限
        /// </summary>
        private DateTime StatutoryPaymentDeadline;
        public DelayTax(DateTime StatutoryPaymentDeadline)
        {
            this.StatutoryPaymentDeadline = StatutoryPaymentDeadline;
        }
        public int Calc(double TotalTax, DateTime DayOfFinishPayingAll)
        {
            // 延滞期間 = 完納日 - 法定納付期限
            return 0 >= (DayOfFinishPayingAll - this.StatutoryPaymentDeadline.AddMonths(2)).TotalDays
                ? (int)((TotalTax * 0.073 * (DayOfFinishPayingAll - StatutoryPaymentDeadline).TotalDays) / 365)
                : (int)(((TotalTax * 0.073 * (StatutoryPaymentDeadline.AddMonths(2) - StatutoryPaymentDeadline).TotalDays)
                    + (TotalTax * 0.146 * (DayOfFinishPayingAll - StatutoryPaymentDeadline.AddMonths(2)).TotalDays)) / 365);
        }
    }
    /// <summary>
    /// 加算税
    /// </summary>
    class AdditionalTax
    {
        private int AlreadyPaid;
        private int SurchargeTaxAmount;
        public AdditionalTax(int TotalTax, int AlreadyPaid = 0)
        {
            this.AlreadyPaid = AlreadyPaid;
            this.SurchargeTaxAmount = TotalTax - AlreadyPaid;
        }
        private int ThreeSectionsOperation(bool Condition, int RetNumWhenTrue, int RetNumWhenFalse)
        {
            return Condition ? RetNumWhenTrue : RetNumWhenFalse;
        }
        /// <summary>
        /// 過少申告加算税
        /// </summary>
        /// <returns>過少申告加算税の金額</returns>
        public int UnderReporting()
        {
            return this.ThreeSectionsOperation(
                this.AlreadyPaid <= 500,
                ThreeSectionsOperation(
                    this.SurchargeTaxAmount <= 500,
                    this.SurchargeTaxAmount / 10,
                    50 + ((this.SurchargeTaxAmount - 50) * 3 / 20)
                    ),
                ThreeSectionsOperation(
                    this.SurchargeTaxAmount <= this.AlreadyPaid,
                    this.SurchargeTaxAmount / 10,
                    this.AlreadyPaid / 10 + ((this.SurchargeTaxAmount - this.AlreadyPaid) * 3 / 20)
                    )
                );
        }
        /// <summary>
        /// 無申告加算税
        /// </summary>
        /// <returns>無申告加算税の金額</returns>
        public int Undeclared()
        {
            return ThreeSectionsOperation(
                this.SurchargeTaxAmount < 500,
                this.SurchargeTaxAmount * 3 / 20,
                75 + ((this.SurchargeTaxAmount - 75) / 5)
                );
        }
        /// <summary>
        /// 重加算税
        /// </summary>
        /// <param name="Undeclared">無申告であるかどうか</param>
        /// <returns>重加算税の金額</returns>
        public int Heavy(bool Undeclared)
        {
            return ThreeSectionsOperation(
                Undeclared,
                this.SurchargeTaxAmount * 2 / 5,
                this.SurchargeTaxAmount * 7 / 20
                );
        }
        // 不納付加算税
        public int NoPayment()
        {
            return SurchargeTaxAmount / 10;
        }
    }
}
