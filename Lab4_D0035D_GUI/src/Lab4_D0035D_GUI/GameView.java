package Lab4_D0035D_GUI;

import java.awt.*;
import java.util.*;

import javax.swing.*;


@SuppressWarnings("serial")
public class GameView extends JFrame{
	
	private JPanel panel;

	private Hashtable <Integer, Integer[]> locations;
	int playerID;

	

	public GameView() {
		locations = new Hashtable <Integer, Integer[]>();
		
		setupGame();
	}

	
	@SuppressWarnings("serial")
	private void setupGame() {
		this.setLayout(new BorderLayout());
		panel = new JPanel() {
			public void paintComponent(Graphics g) {
				super.paintComponent(g);
				g.setColor(Color.black);
				for(int y = 0; y < 1000; y += 50) {
					for(int x= 0; x < 1000; x += 50){
						g.setColor(Color.black);
						g.drawRect(x, y, 50, 50);
						if (checkIfLocation(x/50, y/50)) {
							if(checkIfLocationMine(x/50, y/50)) {
								g.setColor(Color.black);
								g.fillOval(x, y, 50, 50);
							} else {
								g.setColor(Color.blue);
								g.fillOval(x, y, 50, 50);
							}
						}
					}
				}
			}
		};
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		
		panel.setPreferredSize(new Dimension(1000, 1000));
		panel.setBackground(Color.white);
		panel.setVisible(true);
		this.add(panel, BorderLayout.CENTER);
		this.pack();
		this.setVisible(true);
		this.setResizable(false);
		this.setTitle("Game Frame");
	}
	
	boolean checkIfLocation(int x, int y) {
		Set<Integer> keys = locations.keySet();
		for(Integer key: keys) {
			if ((x == locations.get(key)[0] && (y == locations.get(key)[1]))) {
				return true;
			} else {
				continue;
			}
		}
		return false;
	}
	
	boolean checkIfLocationMine(int x, int y) {
		if((locations.get(playerID)[0] == x) && (locations.get(playerID)[1] == y)) {
			return true;
		} else {
			return false;
		}
	}
}


