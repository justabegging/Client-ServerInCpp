package Lab4_D0035D_GUI;
import java.awt.*;
import java.util.Set;
 
import javax.swing.*;
 
 
@SuppressWarnings("serial")
public class Lab4View extends JFrame{
     
    private JPanel panel;
    private Lab4Model model;
     
    public Lab4View(Lab4Model model){
        this.setSize(215,238);
        setupGame();
        this.model = model;
    }
     
    private void setupGame(){
        this.setDefaultCloseOperation(EXIT_ON_CLOSE);
        this.setLayout(new BorderLayout());
        panel = new JPanel(){
            public void paintComponent(Graphics g){
                super.paintComponent(g);
                g.setColor(Color.black);
                Set<Integer> keys = model.locations.keySet();
                for(Integer key: keys){
                    if(key == model.getID()){
                        g.setColor(Color.red);
                        g.fillOval(model.locations.get(key)[0], model.locations.get(key)[1], 5, 5);
                    }else{
                        g.setColor(Color.black);
                        g.fillOval(model.locations.get(key)[0], model.locations.get(key)[1], 5, 5);
                    }
                }
            }
        };
        panel.setBackground(Color.white);
        panel.setPreferredSize(new Dimension(200,200));
        this.add(panel, BorderLayout.CENTER);
        this.setVisible(true);
    }
}

