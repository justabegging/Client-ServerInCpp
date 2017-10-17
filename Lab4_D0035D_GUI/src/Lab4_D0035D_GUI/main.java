package Lab4_D0035D_GUI;

import java.net.Socket;



public class main {
	
	public static void main(String[] args) {
		
		Socket thesocket = null;
		PlayerHandler theHandler;
		JavaServer theServer = null;
		GameView theView;
		theHandler = new PlayerHandler(thesocket, theServer);
		theHandler.start();
	}
}
