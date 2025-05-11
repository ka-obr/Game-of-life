import lib.Size;

import javax.swing.*;

public class game_of_life {
    public static void main(String[] args) {
        // Pobranie szerokości planszy
        String widthInput = JOptionPane.showInputDialog(null, "Enter the width of the world:", "World Initialization", JOptionPane.QUESTION_MESSAGE);
        int width = Integer.parseInt(widthInput);

        // Pobranie wysokości planszy
        String heightInput = JOptionPane.showInputDialog(null, "Enter the height of the world:", "World Initialization", JOptionPane.QUESTION_MESSAGE);
        int height = Integer.parseInt(heightInput);

        // Utworzenie świata z podanymi wymiarami
        World world = new World(new Size(width, height));
        Gameplay gameplay = new Gameplay(world);
    }
}
