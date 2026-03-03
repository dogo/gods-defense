/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey;

import AnyKey.MapCanvas;
import AnyKey.Waves;
import AnyKey.util.CreateXML;
import java.awt.Color;
import java.awt.Cursor;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.util.Vector;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.BorderFactory;
import javax.swing.GroupLayout;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JFileChooser;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.JToggleButton;
import javax.swing.LayoutStyle;

public class MapWindow
extends JFrame
implements ActionListener {
    private MapCanvas mC;
    private CreateXML mCreateXML;
    public Vector<Waves> mWavesVector = new Vector<Waves>();
    public static MapWindow mMapWindowReference = null;
    private final String FULL_NAME = "Gods-Defense Map Generator ";
    private final String MAJOR_VERSION = "0";
    private final String MINOR_VERSION = "1";
    private final String REVISION = "194";
    private JButton jBClose;
    private JButton jBGenerate;
    private JButton jButtonAddWave;
    private JButton jButtonLoadPNG;
    private JButton jButtonRemove;
    private JButton jButtonSave2PNG;
    private JCheckBox jCheckBoxEndPoint;
    private JCheckBox jCheckBoxIsBoss;
    private JCheckBox jCheckBoxStartPoint;
    private JComboBox<String> jComboBoxCheckpoint;
    private JComboBox<String> jComboBoxWaves;
    private JLabel jLabelEnemyFolder;
    private JLabel jLabelEnemyPathArea;
    private JLabel jLabelGold;
    private JLabel jLabelInitializers;
    private JLabel jLabelIntervalSpawnTime;
    private JLabel jLabelLives;
    private JLabel jLabelMapDescription;
    private JLabel jLabelMapName;
    private JLabel jLabelNumberOfEnemies;
    private JLabel jLabelTowerArea;
    private JLabel jLabelWaveDescription;
    private JLabel jLabelWavesAdded;
    private JLabel jLabelColorSwatchRed;
    private JLabel jLabelColorSwatchGreen;
    private JPanel jPanelCheckpoint;
    private JPanel jPanelWaves;
    private JScrollPane jScrollPane1;
    private JScrollPane jScrollPane2;
    private JTextArea jTextAreaMapDescription;
    private JTextArea jTextAreaWaveDescription;
    private JTextField jTextFieldEnemyFolder;
    private JTextField jTextFieldGold;
    private JTextField jTextFieldIntervalSpawnTime;
    private JTextField jTextFieldLives;
    private JTextField jTextFieldMapName;
    private JTextField jTextFieldNumerOfEnemies;
    private JToggleButton jToggleButtonCheckpoint;

    public MapWindow() {
        this.setTitleAndIcon();
        this.mC = new MapCanvas();
        this.initComponents();
        mMapWindowReference = this;
        this.jBGenerate.addActionListener(this);
        this.jBClose.addActionListener(this);
        this.mCreateXML = new CreateXML();
    }

    private void initComponents() {
        this.jBGenerate = new JButton();
        this.jBClose = new JButton();

        this.jLabelColorSwatchRed = new JLabel();
        this.jLabelColorSwatchRed.setOpaque(true);
        this.jLabelColorSwatchRed.setBackground(Color.RED);
        this.jLabelColorSwatchRed.setPreferredSize(new Dimension(32, 32));
        this.jLabelColorSwatchRed.setMinimumSize(new Dimension(32, 32));
        this.jLabelColorSwatchRed.setMaximumSize(new Dimension(32, 32));
        this.jLabelColorSwatchRed.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        this.jLabelColorSwatchRed.setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
        this.jLabelColorSwatchRed.addMouseListener(new MouseAdapter() {
            @Override public void mouseClicked(MouseEvent e) {
                mC.setColor(Color.RED);
                jLabelColorSwatchRed.setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
                jLabelColorSwatchGreen.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
            }
        });

        this.jLabelColorSwatchGreen = new JLabel();
        this.jLabelColorSwatchGreen.setOpaque(true);
        this.jLabelColorSwatchGreen.setBackground(Color.GREEN);
        this.jLabelColorSwatchGreen.setPreferredSize(new Dimension(32, 32));
        this.jLabelColorSwatchGreen.setMinimumSize(new Dimension(32, 32));
        this.jLabelColorSwatchGreen.setMaximumSize(new Dimension(32, 32));
        this.jLabelColorSwatchGreen.setCursor(Cursor.getPredefinedCursor(Cursor.HAND_CURSOR));
        this.jLabelColorSwatchGreen.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
        this.jLabelColorSwatchGreen.addMouseListener(new MouseAdapter() {
            @Override public void mouseClicked(MouseEvent e) {
                mC.setColor(Color.GREEN);
                jLabelColorSwatchGreen.setBorder(BorderFactory.createLineBorder(Color.BLACK, 3));
                jLabelColorSwatchRed.setBorder(BorderFactory.createLineBorder(Color.BLACK, 1));
            }
        });

        this.jLabelTowerArea = new JLabel();
        this.jLabelEnemyPathArea = new JLabel();
        this.jLabelMapName = new JLabel();
        this.jTextFieldMapName = new JTextField();
        this.jLabelMapDescription = new JLabel();
        this.jScrollPane1 = new JScrollPane();
        this.jTextAreaMapDescription = new JTextArea();
        this.jLabelInitializers = new JLabel();
        this.jTextFieldGold = new JTextField();
        this.jLabelGold = new JLabel();
        this.jLabelLives = new JLabel();
        this.jTextFieldLives = new JTextField();
        this.jPanelWaves = new JPanel();
        this.jLabelIntervalSpawnTime = new JLabel();
        this.jTextFieldIntervalSpawnTime = new JTextField();
        this.jLabelWaveDescription = new JLabel();
        this.jScrollPane2 = new JScrollPane();
        this.jTextAreaWaveDescription = new JTextArea();
        this.jLabelNumberOfEnemies = new JLabel();
        this.jLabelEnemyFolder = new JLabel();
        this.jTextFieldNumerOfEnemies = new JTextField();
        this.jTextFieldEnemyFolder = new JTextField();
        this.jComboBoxWaves = new JComboBox<String>();
        this.jLabelWavesAdded = new JLabel();
        this.jButtonAddWave = new JButton();
        this.jButtonRemove = new JButton();
        this.jCheckBoxIsBoss = new JCheckBox();
        this.jPanelCheckpoint = new JPanel();
        this.jToggleButtonCheckpoint = new JToggleButton();
        this.jComboBoxCheckpoint = new JComboBox<String>();
        this.jCheckBoxStartPoint = new JCheckBox();
        this.jCheckBoxEndPoint = new JCheckBox();
        this.jButtonLoadPNG = new JButton();
        this.jButtonSave2PNG = new JButton();

        this.setDefaultCloseOperation(3);
        this.setResizable(false);

        this.jBGenerate.setText("Generate");
        this.jBGenerate.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jBGenerateActionPerformed(evt); }
        });
        this.jBClose.setText("Close");
        this.jBClose.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jBCloseActionPerformed(evt); }
        });
        this.jLabelTowerArea.setText("Tower Area");
        this.jLabelEnemyPathArea.setText("Enemy Path Area");
        this.jLabelMapName.setText("Map Name");
        this.jLabelMapDescription.setText("Map Description");
        this.jTextAreaMapDescription.setColumns(20);
        this.jTextAreaMapDescription.setRows(5);
        this.jScrollPane1.setViewportView(this.jTextAreaMapDescription);
        this.jLabelInitializers.setText("Initializers");
        this.jLabelGold.setText("Gold");
        this.jLabelLives.setText("Lives");
        this.jPanelWaves.setBorder(BorderFactory.createTitledBorder("Waves"));
        this.jLabelIntervalSpawnTime.setText("Interval Spawn Time");
        this.jLabelWaveDescription.setText("Wave Description");
        this.jTextAreaWaveDescription.setColumns(20);
        this.jTextAreaWaveDescription.setRows(5);
        this.jScrollPane2.setViewportView(this.jTextAreaWaveDescription);
        this.jLabelNumberOfEnemies.setText("Number Of Enemies");
        this.jLabelEnemyFolder.setText("Enemy Folder");
        this.jLabelWavesAdded.setText("Waves Added");
        this.jButtonAddWave.setText("Add");
        this.jButtonAddWave.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jButtonAddWaveActionPerformed(evt); }
        });
        this.jButtonRemove.setText("Remove");
        this.jButtonRemove.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jButtonRemoveActionPerformed(evt); }
        });
        this.jCheckBoxIsBoss.setText("Is Boss ?");

        GroupLayout jPanelWavesLayout = new GroupLayout(this.jPanelWaves);
        this.jPanelWaves.setLayout(jPanelWavesLayout);
        jPanelWavesLayout.setHorizontalGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelWavesLayout.createSequentialGroup().addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jLabelWaveDescription).addGroup(jPanelWavesLayout.createSequentialGroup().addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.TRAILING, false).addGroup(GroupLayout.Alignment.LEADING, jPanelWavesLayout.createSequentialGroup().addComponent(this.jLabelEnemyFolder).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextFieldEnemyFolder)).addGroup(GroupLayout.Alignment.LEADING, jPanelWavesLayout.createSequentialGroup().addComponent(this.jLabelNumberOfEnemies).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextFieldNumerOfEnemies)).addComponent(this.jScrollPane2, GroupLayout.Alignment.LEADING, -2, -1, -2)).addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelWavesLayout.createSequentialGroup().addGap(48, 48, 48).addComponent(this.jButtonAddWave, -2, 65, -2).addGap(32, 32, 32).addComponent(this.jButtonRemove)).addGroup(jPanelWavesLayout.createSequentialGroup().addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jCheckBoxIsBoss))).addGap(25, 25, 25)).addGroup(jPanelWavesLayout.createSequentialGroup().addComponent(this.jLabelIntervalSpawnTime).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jTextFieldIntervalSpawnTime, -2, 69, -2).addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelWavesLayout.createSequentialGroup().addGap(62, 62, 62).addComponent(this.jComboBoxWaves, 0, 174, Short.MAX_VALUE)).addGroup(GroupLayout.Alignment.TRAILING, jPanelWavesLayout.createSequentialGroup().addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jLabelWavesAdded).addGap(64, 64, 64))))).addContainerGap()));
        jPanelWavesLayout.setVerticalGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelWavesLayout.createSequentialGroup().addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelWavesLayout.createSequentialGroup().addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabelIntervalSpawnTime).addComponent(this.jTextFieldIntervalSpawnTime, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jLabelWaveDescription).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jScrollPane2, -2, -1, -2)).addGroup(jPanelWavesLayout.createSequentialGroup().addContainerGap().addComponent(this.jLabelWavesAdded).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addComponent(this.jComboBoxWaves, -2, -1, -2).addGap(18, 18, 18).addComponent(this.jCheckBoxIsBoss))).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jLabelNumberOfEnemies).addComponent(this.jTextFieldNumerOfEnemies, -2, -1, -2)).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED).addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.TRAILING).addComponent(this.jLabelEnemyFolder).addGroup(jPanelWavesLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jTextFieldEnemyFolder, -2, -1, -2).addComponent(this.jButtonRemove).addComponent(this.jButtonAddWave))).addContainerGap(21, Short.MAX_VALUE)));

        this.jPanelCheckpoint.setBorder(BorderFactory.createTitledBorder("Checkpoints"));
        this.jToggleButtonCheckpoint.setText("Add Checkpoint OFF");
        this.jToggleButtonCheckpoint.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jToggleButtonCheckpointActionPerformed(evt); }
        });
        this.jCheckBoxStartPoint.setText("Start Point");
        this.jCheckBoxEndPoint.setText("End Point");
        GroupLayout jPanelCheckpointLayout = new GroupLayout(this.jPanelCheckpoint);
        this.jPanelCheckpoint.setLayout(jPanelCheckpointLayout);
        jPanelCheckpointLayout.setHorizontalGroup(jPanelCheckpointLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(jPanelCheckpointLayout.createSequentialGroup().addContainerGap().addGroup(jPanelCheckpointLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(this.jComboBoxCheckpoint, 0, 192, Short.MAX_VALUE).addGroup(jPanelCheckpointLayout.createSequentialGroup().addComponent(this.jCheckBoxStartPoint).addGap(18, 18, 18).addComponent(this.jCheckBoxEndPoint)).addComponent(this.jToggleButtonCheckpoint)).addContainerGap()));
        jPanelCheckpointLayout.setVerticalGroup(jPanelCheckpointLayout.createParallelGroup(GroupLayout.Alignment.LEADING).addGroup(GroupLayout.Alignment.TRAILING, jPanelCheckpointLayout.createSequentialGroup().addComponent(this.jToggleButtonCheckpoint).addPreferredGap(LayoutStyle.ComponentPlacement.RELATED, 13, Short.MAX_VALUE).addGroup(jPanelCheckpointLayout.createParallelGroup(GroupLayout.Alignment.BASELINE).addComponent(this.jCheckBoxStartPoint).addComponent(this.jCheckBoxEndPoint)).addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED).addComponent(this.jComboBoxCheckpoint, -2, -1, -2).addContainerGap()));

        this.jButtonLoadPNG.setText("Load Png");
        this.jButtonLoadPNG.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jButtonLoadPNGActionPerformed(evt); }
        });
        this.jButtonSave2PNG.setText("Save 2 Png");
        this.jButtonSave2PNG.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent evt) { jButtonSave2PNGActionPerformed(evt); }
        });

        // ── Root layout: BorderLayout ──────────────────────────────────────
        // LEFT:   BoxLayout panel — canvas on top, swatches directly below
        // CENTER: right-side form (GroupLayout)
        // SOUTH:  button bar
        this.getContentPane().setLayout(new java.awt.BorderLayout(11, 0));

        // ── Left panel: canvas + swatches ─────────────────────────────────
        JPanel jPanelLeft = new JPanel();
        jPanelLeft.setLayout(new javax.swing.BoxLayout(jPanelLeft, javax.swing.BoxLayout.Y_AXIS));
        jPanelLeft.setBorder(BorderFactory.createEmptyBorder(10, 10, 0, 0));

        this.mC.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        jPanelLeft.add(this.mC);

        jPanelLeft.add(javax.swing.Box.createVerticalStrut(10));

        JPanel jPanelSwatches = new JPanel(new java.awt.FlowLayout(java.awt.FlowLayout.LEFT, 6, 0));
        jPanelSwatches.setAlignmentX(java.awt.Component.LEFT_ALIGNMENT);
        jPanelSwatches.add(this.jLabelColorSwatchRed);
        jPanelSwatches.add(this.jLabelTowerArea);
        jPanelSwatches.add(javax.swing.Box.createHorizontalStrut(10));
        jPanelSwatches.add(this.jLabelColorSwatchGreen);
        jPanelSwatches.add(this.jLabelEnemyPathArea);
        jPanelLeft.add(jPanelSwatches);

        this.getContentPane().add(jPanelLeft, java.awt.BorderLayout.WEST);

        // ── South panel: buttons ──────────────────────────────────────────
        JPanel jPanelButtons = new JPanel(new java.awt.FlowLayout(java.awt.FlowLayout.RIGHT, 6, 10));
        jPanelButtons.add(this.jBGenerate);
        jPanelButtons.add(this.jButtonLoadPNG);
        jPanelButtons.add(this.jButtonSave2PNG);
        jPanelButtons.add(this.jBClose);
        this.getContentPane().add(jPanelButtons, java.awt.BorderLayout.SOUTH);

        // ── Center panel: right-side form (GroupLayout) ───────────────────
        JPanel jPanelRight = new JPanel();
        jPanelRight.setBorder(BorderFactory.createEmptyBorder(10, 0, 0, 10));
        GroupLayout layout = new GroupLayout(jPanelRight);
        jPanelRight.setLayout(layout);
        this.getContentPane().add(jPanelRight, java.awt.BorderLayout.CENTER);

        layout.setHorizontalGroup(
            layout.createParallelGroup(GroupLayout.Alignment.LEADING)
            .addComponent(this.jLabelMapName)
            .addComponent(this.jTextFieldMapName)
            .addComponent(this.jLabelMapDescription)
            .addComponent(this.jScrollPane1)
            .addComponent(this.jLabelInitializers)
            .addGroup(layout.createSequentialGroup()
                .addComponent(this.jLabelGold)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(this.jTextFieldGold, -2, 46, -2)
                .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(this.jLabelLives)
                .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(this.jTextFieldLives, -2, 46, -2))
            .addComponent(this.jPanelCheckpoint)
            .addComponent(this.jPanelWaves));

        layout.setVerticalGroup(
            layout.createSequentialGroup()
            .addComponent(this.jLabelMapName)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(this.jTextFieldMapName, -2, -1, -2)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(this.jLabelMapDescription)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addComponent(this.jScrollPane1, -2, -1, -2)
            .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
            .addComponent(this.jLabelInitializers)
            .addPreferredGap(LayoutStyle.ComponentPlacement.RELATED)
            .addGroup(layout.createParallelGroup(GroupLayout.Alignment.BASELINE)
                .addComponent(this.jLabelGold)
                .addComponent(this.jTextFieldGold, -2, -1, -2)
                .addComponent(this.jLabelLives)
                .addComponent(this.jTextFieldLives, -2, -1, -2))
            .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
            .addComponent(this.jPanelCheckpoint, -2, -1, -2)
            .addPreferredGap(LayoutStyle.ComponentPlacement.UNRELATED)
            .addComponent(this.jPanelWaves, -2, -1, -2)
            .addContainerGap(GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

        this.pack();
    }

    private void jBCloseActionPerformed(ActionEvent evt) { System.exit(0); }

    private void jBGenerateActionPerformed(ActionEvent evt) {
        try {
            if (this.canGenerate().booleanValue()) {
                this.mCreateXML.write(this.mCreateXML.createDocument(this));
                this.clearForm();
                this.mC.clear = true;
                JOptionPane.showMessageDialog(null, "Map generated successfully!", "Sucess", 1);
                this.repaint();
            } else {
                JOptionPane.showMessageDialog(null, "Please fill out all fields.", "Error", 0);
            }
        } catch (IOException ex) {
            Logger.getLogger(MapWindow.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void jButtonAddWaveActionPerformed(ActionEvent evt) {
        if (this.canAddWave().booleanValue()) {
            String boss = "";
            this.mWavesVector.add(new Waves(this.getjCheckBoxIsBoss(), this.getjTextFieldNumerOfEnemies(), this.getjTextFieldEnemyFolder(), this.getjTextAreaWaveDescription(), this.getjTextFieldIntervalSpawnTime()));
            if (this.getjCheckBoxIsBoss().booleanValue()) boss = " - Boss";
            this.jComboBoxWaves.addItem("Wave " + this.mWavesVector.size() + " - " + this.getjTextFieldEnemyFolder() + boss);
            this.clearWaves();
        } else {
            JOptionPane.showMessageDialog(null, "Please fill out all the wave fields.", "Error", 0);
        }
    }

    private void jButtonRemoveActionPerformed(ActionEvent evt) {
        if (this.mWavesVector.size() > 0 && this.jComboBoxWaves.getItemCount() > 0) {
            this.mWavesVector.removeElementAt(this.jComboBoxWaves.getSelectedIndex());
            this.jComboBoxWaves.removeItemAt(this.jComboBoxWaves.getSelectedIndex());
            this.updatedComboBox();
        } else {
            JOptionPane.showMessageDialog(null, "There are no waves to remove.", "Error", 0);
        }
    }

    private void jToggleButtonCheckpointActionPerformed(ActionEvent evt) {
        if (this.jToggleButtonCheckpoint.isSelected()) {
            this.jToggleButtonCheckpoint.setText("Add Checkpoint ON");
            this.mC.mCheckButtonIsOn = true;
        } else {
            this.jToggleButtonCheckpoint.setText("Add Checkpoint OFF");
            this.mC.mCheckButtonIsOn = false;
        }
    }

    private void jButtonLoadPNGActionPerformed(ActionEvent evt) {
        JFileChooser fc = new JFileChooser(new File(File.separator + "tmp"));
        fc.showOpenDialog(this);
        File selFile = fc.getSelectedFile();
        try {
            this.mC.setMapAlpha(selFile.getCanonicalPath());
        } catch (IOException ex) {
            Logger.getLogger(MapWindow.class.getName()).log(Level.SEVERE, null, ex);
        }
        this.repaint();
    }

    private void jButtonSave2PNGActionPerformed(ActionEvent evt) {
        if (this.mC.save2Png()) {
            JOptionPane.showMessageDialog(null, "Png Created.", "Sucess", 1);
        } else {
            JOptionPane.showMessageDialog(null, "The map grid is empty or have empty spaces.", "Error", 0);
        }
    }

    private void updatedComboBox() {
        this.jComboBoxWaves.removeAllItems();
        for (int i = 0; i < this.mWavesVector.size(); ++i) {
            String boss = this.mWavesVector.elementAt(i).getIsBoss().booleanValue() ? " - Boss" : "";
            this.jComboBoxWaves.addItem("Wave " + (i + 1) + " - " + this.mWavesVector.elementAt(i).getEnemyFolder() + boss);
        }
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> new MapWindow().setVisible(true));
    }

    public void addCheckpointToCombo(String x, String y) {
        this.jComboBoxCheckpoint.addItem("Checkpoint " + this.mC.click + " - (X: " + x + ", Y: " + y + ")");
    }

    public String getjTextFieldMapName() { return this.jTextFieldMapName.getText(); }
    public Boolean getjCheckBoxIsBoss() { return this.jCheckBoxIsBoss.isSelected(); }
    public String getjTextAreaMapDescription() { return this.jTextAreaMapDescription.getText(); }
    public String getjTextAreaWaveDescription() { return this.jTextAreaWaveDescription.getText(); }
    public String getjTextFieldEnemyFolder() { return this.jTextFieldEnemyFolder.getText(); }
    public String getjTextFieldGold() { return this.jTextFieldGold.getText(); }
    public String getjTextFieldIntervalSpawnTime() { return this.jTextFieldIntervalSpawnTime.getText(); }
    public String getjTextFieldLives() { return this.jTextFieldLives.getText(); }
    public String getjTextFieldNumerOfEnemies() { return this.jTextFieldNumerOfEnemies.getText(); }
    public JCheckBox getjCheckBoxEndPoint() { return this.jCheckBoxEndPoint; }
    public JCheckBox getjCheckBoxStartPoint() { return this.jCheckBoxStartPoint; }

    private Boolean canGenerate() {
        return !(this.getjTextFieldMapName().trim().isEmpty() || this.getjTextAreaMapDescription().trim().isEmpty() || this.getjTextFieldGold().trim().isEmpty() || this.getjTextFieldLives().trim().isEmpty() || this.mCreateXML.genMapCollision().contains("null") || this.jComboBoxWaves.getItemCount() <= 0 || this.jComboBoxCheckpoint.getItemCount() <= 0);
    }

    private Boolean canAddWave() {
        return !(this.getjTextFieldIntervalSpawnTime().trim().isEmpty() || this.getjTextFieldNumerOfEnemies().trim().isEmpty() || this.getjTextFieldEnemyFolder().trim().isEmpty() || this.getjTextAreaWaveDescription().trim().isEmpty());
    }

    private void clearForm() {
        this.jTextAreaMapDescription.setText(null);
        this.jTextAreaWaveDescription.setText(null);
        this.jTextFieldEnemyFolder.setText(null);
        this.jTextFieldGold.setText(null);
        this.jTextFieldIntervalSpawnTime.setText(null);
        this.jTextFieldLives.setText(null);
        this.jTextFieldMapName.setText(null);
        this.jTextFieldNumerOfEnemies.setText(null);
        this.jCheckBoxIsBoss.setSelected(false);
        this.jComboBoxWaves.removeAllItems();
        this.mWavesVector.removeAllElements();
        MapCanvas.mCheckpointsVector.removeAllElements();
        this.jComboBoxCheckpoint.removeAllItems();
        this.mC.click = 0;
        this.jToggleButtonCheckpoint.setSelected(false);
    }

    private void clearWaves() {
        this.jTextFieldEnemyFolder.setText(null);
        this.jTextFieldIntervalSpawnTime.setText(null);
        this.jTextAreaWaveDescription.setText(null);
        this.jTextFieldNumerOfEnemies.setText(null);
        this.jCheckBoxIsBoss.setSelected(false);
    }

    public void setTitleAndIcon() {
        this.setTitle("Gods-Defense Map Generator 0.1 revision 194");
        this.setIconImage(new ImageIcon(this.getClass().getResource("/res/icon.png")).getImage());
    }

    public void actionPerformed(ActionEvent e) {}
}