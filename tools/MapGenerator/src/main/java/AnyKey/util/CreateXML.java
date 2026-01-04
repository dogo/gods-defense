/*
 * Map Generator for 'Gods Defense'
 * @author Diogo Autilio <A.K.A Dogo - diautilio@gmail.com>
 */
package AnyKey.util;

import AnyKey.MapCanvas;
import AnyKey.MapWindow;
import java.io.FileWriter;
import java.io.IOException;
import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;
import org.dom4j.io.OutputFormat;
import org.dom4j.io.XMLWriter;

public class CreateXML {
    public Document createDocument(MapWindow aMapWindow) {
        Document document = DocumentHelper.createDocument();
        Element root = document.addElement("Map");
        root.addElement("Name").addText(aMapWindow.getjTextFieldMapName());
        root.addElement("Description").addCDATA(aMapWindow.getjTextAreaMapDescription());
        root.addElement("Initializers").addAttribute("Gold", aMapWindow.getjTextFieldGold()).addAttribute("Lives", aMapWindow.getjTextFieldLives());
        Element XMLmenu = root.addElement("Menu");
        XMLmenu.addElement("BuildTowerMenu").addAttribute("Y", "0").addAttribute("Folder", "arrow");
        XMLmenu.addElement("BuildTowerMenu").addAttribute("Y", "1").addAttribute("Folder", "fire");
        XMLmenu.addElement("BuildTowerMenu").addAttribute("Y", "2").addAttribute("Folder", "ice");
        XMLmenu.addElement("BuildTowerMenu").addAttribute("Y", "3").addAttribute("Folder", "lightning");
        root.addElement("MapImg").addAttribute("File", aMapWindow.getjTextFieldMapName().toLowerCase() + ".png").addAttribute("Width", "15").addAttribute("Height", "15");
        root.addElement("CollisionMap").addCDATA("\n" + this.genMapCollision());
        Element XMLpath = root.addElement("Path").addAttribute("Name", "default");
        for (int i = 0; i < MapCanvas.mCheckpointsVector.size(); ++i) {
            XMLpath.addElement("Checkpoint").addAttribute("X", MapCanvas.mCheckpointsVector.elementAt(i).getCoordX()).addAttribute("Y", MapCanvas.mCheckpointsVector.elementAt(i).getCoordY()).addAttribute("Radius", MapCanvas.mCheckpointsVector.elementAt(i).getRadius());
        }
        Element XMLwaves = root.addElement("Waves");
        for (int i = 0; i < aMapWindow.mWavesVector.size(); ++i) {
            Element XMLwave = XMLwaves.addElement("Wave").addAttribute("Path", "default").addAttribute("IntervalSpawnTime", aMapWindow.mWavesVector.elementAt(i).getIntervalSpawnTime()).addAttribute("Description", aMapWindow.mWavesVector.elementAt(i).getWaveDescription());
            if (aMapWindow.mWavesVector.elementAt(i).getIsBoss().booleanValue()) {
                XMLwave.addAttribute("Boss", "true");
            }
            XMLwave.addElement("Enemy").addAttribute("Folder", aMapWindow.mWavesVector.elementAt(i).getEnemyFolder()).addAttribute("NumberOfEnemies", aMapWindow.mWavesVector.elementAt(i).getNumberOfEnemies());
        }
        return document;
    }

    public String genMapCollision() {
        String saida = "";
        for (int i = 0; i < 15; ++i) {
            for (int j = 0; j <= 15; ++j) {
                saida = j == 15 ? saida + "\n" : saida + MapCanvas.mCollisionMap[j][i];
            }
        }
        return saida;
    }

    public void write(Document document) throws IOException {
        OutputFormat format = OutputFormat.createPrettyPrint();
        XMLWriter writer = new XMLWriter(new FileWriter("map.xml"), format);
        writer.write(document);
        writer.close();
    }
}
