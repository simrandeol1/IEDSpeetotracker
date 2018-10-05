// application shows you the basic procedure for sending messages.
package examples;

//Import Statements

importorg.smslib.AGateway;

importorg.smslib.IOutboundMessageNotification;

importorg.smslib.Library;

importorg.smslib.OutboundMessage;

importorg.smslib.Service;

importorg.smslib.modem.SerialModemGateway;
//import statements ends


public class SendMessage

{

public void doIt() throws Exception

{

OutboundNotificationoutboundNotification = new OutboundNotification(); System.out.println("Example: Send message from a serial gsm modem."); System.out.println(Library.getLibraryDescription()); System.out.println("Version: " + Library.getLibraryVersion());

SerialModemGateway gateway = new SerialModemGateway("modem.com5", "COM40", 9600, "Huawei", "E1550");

gateway.setInbound(true);

55
gateway.setOutbound(true);

gateway.setSimPin("");

Explicit SMSC address set is required for some modems. gateway.setSmscNumber("+254727348186"); Service.getInstance().setOutboundMessageNotification(outboundNotification); Service.getInstance().addGateway(gateway); Service.getInstance().startService();

System.out.println(); System.out.println("Modem Information:"); System.out.println(" Manufacturer: " + gateway.getManufacturer()); System.out.println(" Model: " + gateway.getModel()); System.out.println(" Serial No: " + gateway.getSerialNo()); System.out.println(" SIM IMSI: " + gateway.getImsi()); System.out.println(" Signal Level: " + gateway.getSignalLevel() + " dBm"); System.out.println(" Battery Level: " + gateway.getBatteryLevel() + "%"); System.out.println();


Send a message synchronously.

OutboundMessagemsg = new OutboundMessage("+254729169305", "pay fine of ksh

10,000");

Service.getInstance().sendMessage(msg);

System.out.println(msg);



System.out.println("Now Sleeping - Hit <enter> to terminate.");

System.in.read();

Service.getInstance().stopService();

}

56


public class OutboundNotification implements IOutboundMessageNotification

{

public void process(AGateway gateway, OutboundMessagemsg)

{

System.out.println("Outbound handler called from Gateway: " + gateway.getGatewayId());

System.out.println(msg);

}

}



public static void main(String args[])

{

SendMessage app = new SendMessage();

try

{

app.doIt();

}

catch (Exception e)

{

e.printStackTrace();

}

}

}






57



































