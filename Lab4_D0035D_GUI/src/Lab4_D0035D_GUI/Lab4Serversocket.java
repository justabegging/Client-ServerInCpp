package Lab4_D0035D_GUI;
import java.io.*;
import java.net.*;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
 
public class Lab4Serversocket extends Thread{
     
    private ServerSocket serverSocket;
    private Socket socket;
    private DataInputStream input;
    private DataOutputStream output;
    private Lab4Controller controller;
     
    public Lab4Serversocket(Lab4Controller controller){
        this.controller = controller;
    }
     
    public void run(){
        setupServerSocket();
        closeSocket();
    }
     
    private void setupServerSocket(){
        try{
            serverSocket = new ServerSocket(6543);
            System.out.println("Waiting for conn..");
            socket = serverSocket.accept();
            System.out.println("Got connection..");
            setupStreams();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
     
    private void setupStreams(){
        try{
            System.out.println("Trying to setup streams..");
            input = new DataInputStream(socket.getInputStream());
            output = new DataOutputStream(socket.getOutputStream());
            System.out.println("Streams are setup!");
            getMessage();
        }catch(Exception e){
            e.printStackTrace();
        }
    }
     
    private void getMessage(){
        while(true){
            try{
                System.out.println("waiting for message..");
                byte recvBuf[] = new byte[1024];
                input.read(recvBuf);
                String recvMsg = new String(recvBuf, StandardCharsets.UTF_8);
                controller.messageHandler(recvMsg);
                System.out.println(recvMsg);
                 
            }catch(Exception e){
                e.printStackTrace();
                break;
            }
        }
    }
     
    void sendMessage(String msg){
        try{
            byte sendBuf[] = new byte[1024];
            sendBuf = msg.getBytes(Charset.forName("ASCII"));
            output.write(sendBuf);
            output.flush();
        }catch(Exception e){
            System.out.println("Couldnt send message over socket!");
        }
    }
     
    private void closeSocket(){
        try{
            System.out.println("Closing streams and socket!");
            input.close();
            output.close();
            socket.close();
            System.out.println("Exiting program!");
        }catch(Exception e){
            e.printStackTrace();
        }
    }
     
}