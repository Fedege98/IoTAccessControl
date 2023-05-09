using System.IO.Ports;
using System.Text;

namespace IotGatewayAccessManager.Console;

public class Worker : BackgroundService
{
    private readonly ILogger<Worker> _logger;
    private readonly SerialPort _serialPort;
    public Worker(ILogger<Worker> logger, SerialPort serialPort)
    {
        _logger = logger;
        _serialPort = serialPort;
    }

    protected override async Task ExecuteAsync(CancellationToken stoppingToken)
    {
        _serialPort.Open();
        _serialPort.DataReceived += _serialPort_DataReceived;
        while (!stoppingToken.IsCancellationRequested)
        {

        }
    }

    private void _serialPort_DataReceived(object sender, SerialDataReceivedEventArgs e)
    {
        var serial = sender as SerialPort;
        var buffer = serial?.BytesToRead;
        if (buffer.HasValue)
        {
            List<byte> bytes = new();
            
            var packetLength = serial!.ReadByte();
            packetLength <<= serial!.ReadByte();
            bytes.AddRange(BitConverter.GetBytes(packetLength));

            for (int i = 0; i < packetLength - 2; i++)
            {
                bytes.Add((byte) serial!.ReadByte());
                
            }
            _logger.LogInformation("{date} {text}", DateTime.Now.ToString("s"),Encoding.ASCII.GetString(bytes.ToArray()));
            serial.Write(bytes.ToArray(),0,bytes.Count);
            serial.DiscardOutBuffer();
        }   
    }
}
