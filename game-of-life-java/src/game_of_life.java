import lib.Size;

import javax.swing.*;
import java.awt.*;
import java.lang.reflect.InvocationTargetException;

public class game_of_life {
    public static void main(String[] args) {
        String widthInput = JOptionPane.showInputDialog(null, "Enter the width of the world:", "World Initialization", JOptionPane.QUESTION_MESSAGE);
        int width = Integer.parseInt(widthInput);

        String heightInput = JOptionPane.showInputDialog(null, "Enter the height of the world:", "World Initialization", JOptionPane.QUESTION_MESSAGE);
        int height = Integer.parseInt(heightInput);

        World world = new World(new Size(width, height));
        Gameplay gameplay = new Gameplay(world);
    }
}