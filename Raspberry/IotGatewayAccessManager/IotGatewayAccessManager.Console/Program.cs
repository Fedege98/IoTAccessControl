using System.IO.Ports;
using IotGatewayAccessManager.Console;

IHost host = Host.CreateDefaultBuilder(args)
    .ConfigureServices(services =>
    {
        services.AddSingleton(sp =>
            new SerialPort
            {
                BaudRate = 115200,
                Parity = Parity.None,
                PortName = "COM2",
                StopBits = StopBits.One,
                WriteTimeout = 200,
                ReadTimeout = 2000,
                
            }
            );
        services.AddHostedService<Worker>();
    })
    .Build();

host.Run();
