package Lab4_D0035D_GUI;
import java.util.Hashtable;


public class Lab4Model {
     
    Hashtable<Integer, Integer[]> locations;
    private int playerID;
     
    public Lab4Model(){
        locations = new Hashtable<Integer, Integer[]>();
    }
     
    void setID(int id){
        playerID = id;
    }
     
    void updateLocations(int id, Integer[] xy){
        locations.put(id, xy);
    }
     
    void removeLocation(int id){
        locations.remove(id);
    }
     
    int getID(){
        return playerID;
    }
}