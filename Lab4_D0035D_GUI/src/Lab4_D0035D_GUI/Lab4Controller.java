package Lab4_D0035D_GUI;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
 
 
public class Lab4Controller {
     
    Lab4Model model;
    Lab4View view;
    Lab4Serversocket socket;
     
    public Lab4Controller(Lab4View view, Lab4Model model){
        this.model = model;
        this.view = view;
        socket = new Lab4Serversocket(this);
        socket.start();
        initiateKeys();
    }
     
    private void initiateKeys(){
        view.addKeyListener(new KeyListener(){
 
            public void keyTyped(KeyEvent e) {
            }
 
            @Override
            public void keyPressed(KeyEvent e) {
                int key = e.getKeyCode();
                if(key == KeyEvent.VK_W){
                    socket.sendMessage("1");
                }else if(key == KeyEvent.VK_A){
                    socket.sendMessage("2");
                }else if(key == KeyEvent.VK_S){
                    socket.sendMessage("3");
                }else if(key == KeyEvent.VK_D){
                    socket.sendMessage("4");
                }
            }
 
            @Override
            public void keyReleased(KeyEvent e) {
            }
             
        });
    }
     
    void messageHandler(String msg){
        String[] divide = msg.split(";");
        for(int i = 0; i < divide.length; i++){
            if(divide[i].equals("MyId")){
                model.setID(Integer.parseInt(divide[i+1]));
                view.repaint();
            }else if(divide[i].equals("NewPlayerPosition")){
                Integer xy[] = {Integer.parseInt(divide[i+2])+100,Integer.parseInt(divide[i+3])+100};
                model.updateLocations(Integer.parseInt(divide[i+1]), xy);
                view.repaint();
            }else if(divide[i].equals("PlayerLeave")){
                model.removeLocation(Integer.parseInt(divide[i+1]));
                view.repaint();
            }
        }
    }
     
}
