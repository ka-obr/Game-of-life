import javax.swing.*;
import java.io.*;

public class WorldFileManager {

    private static final String DEFAULT_SAVE_PATH = "save/world.sav";

    public static void saveWorldToFile(World world) {
        try {
            new File("save").mkdirs();
            File file = new File(DEFAULT_SAVE_PATH);
            try (ObjectOutputStream oos = new ObjectOutputStream(new FileOutputStream(file))) {
                oos.writeObject(world);
                JOptionPane.showMessageDialog(null, "World state saved successfully!\nFile: " + file.getAbsolutePath());
            }
        } catch (IOException e) {
            JOptionPane.showMessageDialog(null, "Error saving world state: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static World loadWorldFromFile() {
        File file = new File(DEFAULT_SAVE_PATH);

        if (!file.exists()) {
            JOptionPane.showMessageDialog(null, "File not found: " + file.getAbsolutePath(), "Error", JOptionPane.ERROR_MESSAGE);
            return null;
        }

        try (ObjectInputStream ois = new ObjectInputStream(new FileInputStream(file))) {
            World world = (World) ois.readObject();
            world.setWorldReferenceForAll();
            JOptionPane.showMessageDialog(null, "World state loaded successfully!\nFile: " + file.getAbsolutePath());
            return world;
        } catch (IOException | ClassNotFoundException e) {
            JOptionPane.showMessageDialog(null, "Error loading world state: " + e.getMessage(), "Error", JOptionPane.ERROR_MESSAGE);
        }
        return null;
    }
}
