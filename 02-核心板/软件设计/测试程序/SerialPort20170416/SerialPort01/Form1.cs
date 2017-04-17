using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Text.RegularExpressions;

namespace SerialPort01
{
    public partial class Form1 : Form
    {
        private StringBuilder builder = new StringBuilder();
        private long receivedCount = 0;
        private long sendCount = 0;
        private long checkCount = 0;  //每秒接收的数据个数
        private bool timer80msOpened=false;

        byte[] sendData={0xA5,0x10,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x0,0x35};
        

        public Form1()
        {
            InitializeComponent();

            //添加事件
            this.serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);

            //初始化窗口号和波特率
            string[] ports = SerialPort.GetPortNames();     //静态调用
            Array.Sort(ports);    //排序
            this.comboPortName.Items.AddRange(ports);
            this.comboPortName.SelectedIndex = this.comboPortName.Items.Count > 0 ? 0 : -1;
            this.comboBaurate.SelectedIndex = this.comboBaurate.Items.IndexOf("115200");

            timerCheckReceive.Start();
           


        }

        private void sendBtn_Click(object sender, EventArgs e)
        {
            //n记录发送了几个字节
            int n = 0;
            if(checkBoxSendHex.Checked)
            {
                MatchCollection mc = Regex.Matches(sendTextBox.Text, @"(?i)[/da-f]{2}");
                List<byte> buf = new List<byte>();    //填充到这个临时列表中
                //依次添加到列表中
                foreach(Match m in mc)
                {
                    buf.Add(byte.Parse(m.Value,System.Globalization.NumberStyles.HexNumber));
                }

                //转换列表为数组后发送
                serialPort1.Write(buf.ToArray(), 0, buf.Count);
                //记录发送的字节数
            }
            else  //由于是单行发送所以没有换行符
            {
                serialPort1.Write(sendTextBox.Text);
                n = sendTextBox.Text.Length;
            }

            sendCount += n;
            labelSendCount.Text = "Send count: " + sendCount.ToString();
        }


        private void receiveBtn_Click(object sender, EventArgs e)
        {
            //byte[] data = Convert.FromBase64String(serialPort1.ReadExisting());
            //    serialPort1.ReadChar();
            //receiveTextBox.Text = Encoding.Unicode.GetString(data);
            //serialPort1.Close();

            receiveTextBox.Text += Convert.ToString((char)serialPort1.ReadByte());


        }

        //接收数据处理函数
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            int n = this.serialPort1.BytesToRead;   //记录下来，避免某种原因的错误

            byte[] buf = new byte[n];
            receivedCount += n;
            checkCount++; //没接收一次加1

            this.serialPort1.Read(buf, 0, n);  //读取缓冲数据

            builder.Clear();    //清除字符构造器的内容

            //因为要访问ui资源，所以需要使用invoke方式同步ui
            this.Invoke((EventHandler)(delegate
            {
                //判断是否显示为16进制
                if (this.checkBoxHexView.Checked)
                {
                    //依次拼接出16进制字符
                    foreach (byte b in buf)
                    {
                        builder.Append(b.ToString("X2") + " ");
                    }
                }
                else
                {
                    //直接按ASCII规则转化成字符串
                    builder.Append(Encoding.ASCII.GetString(buf));
                }
                //以追加的形式添加到文本框的末端，并滚动到最后
                this.receiveTextBox.AppendText(builder.ToString());
                //修改计数器显示
                this.labelGetCount.Text = "Get Count: " + receivedCount.ToString();

            }));


        }

        private void OpenBtn_Click(object sender, EventArgs e)
        {
            if(this.serialPort1.IsOpen)
            {
                this.serialPort1.Close();
                timerSendPer80ms.Stop();
                timerSendPer5s.Stop();   //打开发送定时器
            }
            else
            {
                serialPort1.PortName = comboPortName.Text;
              //  serialPort1.BaudRate = comboBaurate.Text;

                try 
                {
                    serialPort1.Open();
                    timerSendPer5s.Start();   //打开发送定时器
                    timerSendPer80ms.Start();  //打开定时器
                }
                catch(Exception ex)
                {
                    serialPort1 = new SerialPort();
                    MessageBox.Show(ex.Message);
                }
            }
            this.OpenBtn.Text = serialPort1.IsOpen ? "Close" : "Open";
            this.sendBtn.Enabled = serialPort1.IsOpen;

        }


        private void resetBtn_Click(object sender, EventArgs e)
        {
            receivedCount = sendCount= 0;
            labelSendCount.Text = "Send count: 0";
            labelGetCount.Text = "Get count: 0";

            receiveTextBox.Clear();
        }

        private void timerCheckReceive_Tick(object sender, EventArgs e)
        {

             //因为要访问ui资源，所以需要使用invoke方式同步ui
            this.Invoke((EventHandler)(delegate
            {

                //修改计数器显示
                this.labelReceiveCounter.Text = "ReceiveCounterPerSecond: " + checkCount.ToString();

            }
            ));
           
            checkCount = 0;


        }

        private void timerSendPer5s_Tick(object sender, EventArgs e)
        {
            //if (timer80msOpened)
            //{
            //    timer80msOpened = !timer80msOpened;
            //    timerSendPer80ms.Stop();
            //}
            //else
            //{
            //    timer80msOpened = !timer80msOpened;
            //    timerSendPer80ms.Start();
            //    sendCount = 0;
            //}
            
        }

        private void timerSendPer80ms_Tick(object sender, EventArgs e)
        {

            updataSendData();
         
            //n记录发送了几个字节
          
            serialPort1.Write(sendData, 0, sendData.Count());

        }

        private void updataSendData()
        {
            sendData[2] = (byte)numericUpDownIndex.Value;
            sendData[3] = (byte)numericUpDownLeftMotor.Value;
            sendData[4] = (byte)numericUpDownRightMotor.Value;
            sendData[5] = (byte)numericUpDownFeedData1.Value;
            sendData[6] = (byte)numericUpDownFeedData2.Value;
            sendData[7] = (byte)numericUpDownFeedData3.Value;
            sendData[8] = (byte)numericUpDownFeedData4.Value;
            sendData[9] = (byte)numericUpDownFeedData5.Value;
            sendData[10] = (byte)numericUpDownFeedData6.Value;

            //求检验和
            sendData[14]=0;
            for (int i = 0; i<14; i++ )
            {
                sendData[14]+=sendData[i];
            }
               

        }


       


    }
}
