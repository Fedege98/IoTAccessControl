using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Runtime.InteropServices;

namespace IotGatewayAccessManager.Console.Models;

[StructLayout(LayoutKind.Sequential)]
public class SharedPacket
{
    [MarshalAs(UnmanagedType.I2)] public int Length;
    [MarshalAs(UnmanagedType.LPStr)] public string SourceDevice;
    [MarshalAs(UnmanagedType.LPStr)] public string TargetDevice;
    [MarshalAs(UnmanagedType.I1)] public PacketType Type;

}


public enum PacketType
{
    PacketDebug = 1,
    PacketGenerate
}
