package Lab4_D0035D_GUI;

public class Main {
	 
    /**
     * @param args
     */
    @SuppressWarnings("unused")
    public static void main(String[] args) {
        Lab4Model model = new Lab4Model();
        Lab4View view = new Lab4View(model);
        Lab4Controller controller = new Lab4Controller(view, model);
    }
 
}