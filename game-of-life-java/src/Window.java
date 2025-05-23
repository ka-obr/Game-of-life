import lib.Size;
import javax.swing.*;
import java.awt.*;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.ComponentAdapter;
import java.awt.event.ComponentEvent;
import javax.imageio.ImageIO;
import java.io.IOException;

public class Window extends JFrame {
    private final int TILE_SIZE = 50;
    private World world;
    private final Gameplay gameplay;
    private int offsetX = 0, offsetY = 0;
    private Point dragStart = null;
    private JPopupMenu activePopupMenu = null;
    private DrawingPanel drawingPanel;
    private JTextArea messageArea;
    private JPanel floatingButtonPanel;

    public Window(Gameplay gameplay) {
        this.world = gameplay.getWorld();
        this.gameplay = gameplay;

        initializeWindow();
        initializeDrawingPanel();
        initializeMessagePanel();
        initializeFloatingButtonPanel(gameplay);
        initializeKeyBindings(gameplay);
        initializeMouseListeners();

        setVisible(true);
    }

    private void initializeWindow() {
        Size gridSize = world.getSize();
        int windowWidth = gridSize.x * TILE_SIZE + 300;
        int windowHeight = gridSize.y * TILE_SIZE + 200;

        setTitle("Karol Obrycki 203264");
        setSize(windowWidth, windowHeight);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setLocationRelativeTo(null);
        setLayout(new BorderLayout());
    }

    private void initializeDrawingPanel() {
        drawingPanel = new DrawingPanel();
        add(drawingPanel, BorderLayout.CENTER);
    }

    private void initializeMessagePanel() {
        messageArea = new JTextArea();
        messageArea.setEditable(false);
        messageArea.setLineWrap(true);
        messageArea.setWrapStyleWord(true);
        messageArea.setBackground(new Color(46, 90, 46));
        messageArea.setForeground(Color.WHITE);
        messageArea.setFont(new Font("Arial", Font.BOLD, 20));
        messageArea.setFocusable(false);

        JScrollPane scrollPane = new JScrollPane(messageArea);
        scrollPane.setPreferredSize(new Dimension(400, getHeight()));
        add(scrollPane, BorderLayout.EAST);
    }

    private void initializeFloatingButtonPanel(Gameplay gameplay) {
        floatingButtonPanel = new JPanel();
        floatingButtonPanel.setFocusable(false);
        floatingButtonPanel.setOpaque(false);
        floatingButtonPanel.setLayout(new BoxLayout(floatingButtonPanel, BoxLayout.Y_AXIS));

        JButton nextTurnButton = createIconButton("images/nextTurn.png", "Next Turn");
        JButton saveButton = createIconButton("images/save.png", "Save");
        JButton loadButton = createIconButton("images/load.png", "Load");
        JButton exitButton = createIconButton("images/exit.png", "Exit");

        floatingButtonPanel.add(nextTurnButton);
        floatingButtonPanel.add(Box.createVerticalStrut(10));
        floatingButtonPanel.add(saveButton);
        floatingButtonPanel.add(Box.createVerticalStrut(10));
        floatingButtonPanel.add(loadButton);
        floatingButtonPanel.add(Box.createVerticalStrut(10));
        floatingButtonPanel.add(exitButton);

        JRootPane root = getRootPane();
        JComponent glass = (JComponent) root.getGlassPane();
        glass.setLayout(null);
        glass.setVisible(true);
        glass.setFocusable(false);
        glass.add(floatingButtonPanel);

        addComponentListener(new ComponentAdapter() {
            @Override
            public void componentResized(ComponentEvent e) {
                positionFloatingPanel();
            }

            @Override
            public void componentShown(ComponentEvent e) {
                positionFloatingPanel();
            }
        });
        positionFloatingPanel();

        nextTurnButton.addActionListener(e -> {
            gameplay.handleInput("");
            drawingPanel.repaint();
        });
        saveButton.addActionListener(e -> gameplay.handleInput("s"));
        loadButton.addActionListener(e -> gameplay.handleInput("l"));
        exitButton.addActionListener(e -> dispose());
    }

    private void initializeKeyBindings(Gameplay gameplay) {
        JRootPane root = getRootPane();
        InputMap inputMap = root.getInputMap(JComponent.WHEN_IN_FOCUSED_WINDOW);
        ActionMap actionMap = root.getActionMap();

        inputMap.put(KeyStroke.getKeyStroke("UP"), "moveUp");
        inputMap.put(KeyStroke.getKeyStroke("DOWN"), "moveDown");
        inputMap.put(KeyStroke.getKeyStroke("LEFT"), "moveLeft");
        inputMap.put(KeyStroke.getKeyStroke("RIGHT"), "moveRight");
        inputMap.put(KeyStroke.getKeyStroke('q'), "quit");
        inputMap.put(KeyStroke.getKeyStroke('s'), "save");
        inputMap.put(KeyStroke.getKeyStroke('l'), "load");
        inputMap.put(KeyStroke.getKeyStroke('r'), "special");
        inputMap.put(KeyStroke.getKeyStroke('t'), "nextTurn");

        actionMap.put("moveUp", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("up");
                drawingPanel.repaint();
            }
        });
        actionMap.put("moveDown", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("down");
                drawingPanel.repaint();
            }
        });
        actionMap.put("moveLeft", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("left");
                drawingPanel.repaint();
            }
        });
        actionMap.put("moveRight", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("right");
                drawingPanel.repaint();
            }
        });
        actionMap.put("quit", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("q");
            }
        });
        actionMap.put("save", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("s");
            }
        });
        actionMap.put("load", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("l");
            }
        });
        actionMap.put("special", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("r");
            }
        });
        actionMap.put("nextTurn", new AbstractAction() {
            public void actionPerformed(ActionEvent e) {
                gameplay.handleInput("");
                drawingPanel.repaint();
            }
        });
    }

    private void initializeMouseListeners() {
        addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    dragStart = e.getPoint();
                } else if (SwingUtilities.isLeftMouseButton(e)) {
                    handleTileClick(e.getPoint());
                }
            }

            @Override
            public void mouseReleased(MouseEvent e) {
                if (SwingUtilities.isRightMouseButton(e)) {
                    dragStart = null;
                }
            }
        });

        addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                if (dragStart != null && SwingUtilities.isRightMouseButton(e)) {
                    int dx = e.getX() - dragStart.x;
                    int dy = e.getY() - dragStart.y;
                    offsetX += dx;
                    offsetY += dy;
                    dragStart = e.getPoint();
                    drawingPanel.repaint();
                }
            }
        });
    }

    private JButton createIconButton(String iconPath, String tooltip) {
        JButton button = new JButton();
        try {
            Image img = ImageIO.read(new java.io.File(iconPath));
            int size = 64;
            ImageIcon icon = new ImageIcon(img.getScaledInstance(size, size, Image.SCALE_SMOOTH));
            button.setIcon(icon);
            button.setContentAreaFilled(false);
            button.setBorder(BorderFactory.createEmptyBorder());
            button.setBorderPainted(false);
            button.setFocusPainted(false);
            button.setOpaque(false);
            button.setPreferredSize(new Dimension(64, 64));
        } catch (IOException e) {
            button.setText(tooltip);
        }
        button.setToolTipText(tooltip);
        return button;
    }

    private void positionFloatingPanel() {
        int panelWidth = floatingButtonPanel.getPreferredSize().width;
        int panelHeight = floatingButtonPanel.getPreferredSize().height;
        int x = 20;
        int y = (getHeight() - panelHeight) / 2;
        floatingButtonPanel.setBounds(x, y, panelWidth, panelHeight);
        getRootPane().getGlassPane().repaint();
    }

    public void addMessage(String message) {
        messageArea.append(message + "\n");
        messageArea.setCaretPosition(messageArea.getDocument().getLength());
    }

    public void clearMessages() {
        messageArea.setText("");
    }

    private class DrawingPanel extends JPanel {
        @Override
        protected void paintComponent(Graphics g) {
            super.paintComponent(g);


            g.setColor(new Color(46, 90, 46));
            g.fillRect(0, 0, getWidth(), getHeight());

            drawWorld(g);
        }

        private void drawWorld(Graphics g) {
            Graphics2D g2d = (Graphics2D) g;

            Size size = world.getSize();
            int gridWidth = size.x * TILE_SIZE;
            int gridHeight = size.y * TILE_SIZE;

            int centerX = (getWidth() - gridWidth) / 2;
            int centerY = (getHeight() - gridHeight) / 2;

            g2d.translate(offsetX + centerX, offsetY + centerY);

            for (int i = 0; i < size.x; i++) {
                for (int j = 0; j < size.y; j++) {
                    g2d.setColor(new Color(67, 131, 67));
                    g2d.fillRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);

                    g2d.setColor(new Color(46, 90, 46));
                    g2d.setStroke(new BasicStroke(3));
                    g2d.drawRect(i * TILE_SIZE, j * TILE_SIZE, TILE_SIZE, TILE_SIZE);
                }
            }

            for (Organism organism : world.getOrganisms()) {
                Point position = organism.getPosition();
                ImageIcon icon = organism.getIcon();

                if (icon != null) {
                    Image image = icon.getImage();
                    int imageWidth = (int) (TILE_SIZE * 0.8);
                    int imageHeight = (int) (TILE_SIZE * 0.8);

                    int xOffset = (TILE_SIZE - imageWidth) / 2;
                    int yOffset = (TILE_SIZE - imageHeight) / 2 + 1;

                    g2d.drawImage(image, position.x * TILE_SIZE + xOffset, position.y * TILE_SIZE + yOffset, imageWidth, imageHeight, this);
                }
            }
        }
    }

    private void handleTileClick(Point clickPoint) {
        Size size = world.getSize();
        int tileWidth = 50;
        int tileHeight = 50;

        int gridWidth = size.x * tileWidth;
        int gridHeight = size.y * tileHeight;
        int centerX = (getWidth() - gridWidth) / 2 - 200; //FIX
        int centerY = (getHeight() - gridHeight) / 2 + 17;

        int adjustedX = clickPoint.x - offsetX - centerX;
        int adjustedY = clickPoint.y - offsetY - centerY;

        int tileX = adjustedX / tileWidth;
        int tileY = adjustedY / tileHeight;

        if (tileX >= 0 && tileX < size.x && tileY >= 0 && tileY < size.y && adjustedX >= 0 && adjustedY >= 0) {
            showAddMenu(tileX, tileY);
        }
    }

    private <T extends Animal> void addAnimalOption(JPopupMenu popupMenu, Class<T> animalClass, ImageIcon icon, Point tilePosition) {
        JMenuItem menuItem = new JMenuItem(icon);
        menuItem.setOpaque(false);
        menuItem.setBorder(BorderFactory.createEmptyBorder());
        menuItem.addActionListener(e -> {
            try {
                T animal = animalClass.getConstructor(Point.class, World.class, int.class)
                        .newInstance(tilePosition, world, 1);
                world.addOrganism(animal);

                if (animal instanceof Human) {
                    gameplay.setHuman((Human) animal);
                }

                drawingPanel.repaint();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        popupMenu.add(menuItem);
    }

    private <T extends Plant> void addPlantOption(JPopupMenu popupMenu, Class<T> plantClass, ImageIcon icon, Point tilePosition) {
        JMenuItem menuItem = new JMenuItem(icon);
        menuItem.setOpaque(false);
        menuItem.setBorder(BorderFactory.createEmptyBorder());
        menuItem.addActionListener(e -> {
            try {
                T plant = plantClass.getConstructor(Point.class, World.class, int.class)
                        .newInstance(tilePosition, world, 1);
                world.addOrganism(plant);
                drawingPanel.repaint();
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        });
        popupMenu.add(menuItem);
    }

    //ADD MENU

    private void showAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        if (world.isTileOccupied(tilePosition)) {
            return;
        }

        closeActivePopupMenu();

        JPopupMenu categoryMenu = createCategoryMenu(tileX, tileY);
        showPopupMenu(categoryMenu, tileX, tileY);
    }

    private JPopupMenu createCategoryMenu(int tileX, int tileY) {
        JPopupMenu categoryMenu = new JPopupMenu();
        activePopupMenu = categoryMenu;

        JMenuItem animalOption = new JMenuItem("Animal");
        animalOption.addActionListener(e -> {
            categoryMenu.setVisible(false);
            showAnimalAddMenu(tileX, tileY);
        });
        categoryMenu.add(animalOption);

        JMenuItem plantOption = new JMenuItem("Plant");
        plantOption.addActionListener(e -> {
            categoryMenu.setVisible(false);
            showPlantAddMenu(tileX, tileY);
        });
        categoryMenu.add(plantOption);

        return categoryMenu;
    }

    private void showAnimalAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        JPopupMenu animalMenu = createAnimalMenu(tilePosition);
        showPopupMenu(animalMenu, tileX, tileY);
    }

    private void showPlantAddMenu(int tileX, int tileY) {
        Point tilePosition = new Point(tileX, tileY);
        JPopupMenu plantMenu = createPlantMenu(tilePosition);
        showPopupMenu(plantMenu, tileX, tileY);
    }

    private JPopupMenu createAnimalMenu(Point tilePosition) {
        JPopupMenu animalMenu = new JPopupMenu();
        activePopupMenu = animalMenu;

        addAnimalOption(animalMenu, Sheep.class, new ImageIcon(Sheep.scaledSheepIcon), tilePosition);
        addAnimalOption(animalMenu, Wolf.class, new ImageIcon(Wolf.scaledWolfIcon), tilePosition);
        addAnimalOption(animalMenu, Fox.class, new ImageIcon(Fox.scaledFoxIcon), tilePosition);
        addAnimalOption(animalMenu, Turtle.class, new ImageIcon(Turtle.scaledTurtleIcon), tilePosition);
        addAnimalOption(animalMenu, Antelope.class, new ImageIcon(Antelope.scaledAntelopeIcon), tilePosition);

        boolean humanExists = world.getOrganisms().stream().anyMatch(o -> o instanceof Human);
        if (!humanExists) {
            addAnimalOption(animalMenu, Human.class, new ImageIcon(Human.scaledHumanIcon), tilePosition);
        }

        return animalMenu;
    }

    private JPopupMenu createPlantMenu(Point tilePosition) {
        JPopupMenu plantMenu = new JPopupMenu();
        activePopupMenu = plantMenu;

        addPlantOption(plantMenu, Grass.class, new ImageIcon(Grass.scaledGrassIcon), tilePosition);
        addPlantOption(plantMenu, Dandelion.class, new ImageIcon(Dandelion.scaledDandelionIcon), tilePosition);
        addPlantOption(plantMenu, Guarana.class, new ImageIcon(Guarana.scaledGuaranaIcon), tilePosition);
        addPlantOption(plantMenu, Nightshade.class, new ImageIcon(Nightshade.scaledNightshadeIcon), tilePosition);
        addPlantOption(plantMenu, Hogweed.class, new ImageIcon(Hogweed.scaledHogweedIcon), tilePosition);

        return plantMenu;
    }

    private void showPopupMenu(JPopupMenu menu, int tileX, int tileY) {
        int tileWidth = TILE_SIZE, tileHeight = TILE_SIZE;
        int gridWidth = world.getSize().x * tileWidth;
        int gridHeight = world.getSize().y * tileHeight;
        int panelCenterX = (drawingPanel.getWidth() - gridWidth) / 2;
        int panelCenterY = (drawingPanel.getHeight() - gridHeight) / 2;
        int tileCenterX = offsetX + panelCenterX + tileX * tileWidth + tileWidth / 2;
        int tileCenterY = offsetY + panelCenterY + tileY * tileHeight + tileHeight / 2;
        Dimension popupSize = menu.getPreferredSize();
        int popupX = tileCenterX - popupSize.width / 2;
        int popupY = tileCenterY - popupSize.height / 2;
        menu.show(drawingPanel, popupX, popupY);
    }

    private void closeActivePopupMenu() {
        if (activePopupMenu != null) {
            activePopupMenu.setVisible(false);
            activePopupMenu = null;
            drawingPanel.repaint();
        }
    }

    public void setWorld(World loaded) {
        this.world = loaded;
        loaded.setWindow(this);
        drawingPanel.repaint();
        addMessage("World loaded from file.");
    }
}
