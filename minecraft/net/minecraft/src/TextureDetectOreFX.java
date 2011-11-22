// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.geom.AffineTransform;
import java.awt.image.AffineTransformOp;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.print.attribute.standard.Media;

import net.minecraft.client.Minecraft;

// Referenced classes of package net.minecraft.src:
//            TextureFX, Item, World, ChunkCoordinates, 
//            EntityPlayerSP, WorldProvider

public class TextureDetectOreFX extends TextureFX
{
    public TextureDetectOreFX(int iDetectorIconID, int iBlockID, int itemIconIndex)
    {
    	super(iDetectorIconID);
    	
        detectOreIconImageData			= new int[256];
        
        tileImage = 1;
        mc = ModLoader.getMinecraftInstance();
        iDetectedBlockID = iBlockID;
        
        try
        {
            BufferedImage bufferedimage = ImageIO.read((net.minecraft.client.Minecraft.class).getResource("/gui/oreDetector2.png"));
            bufferedimage.getRGB(0, 0, 16, 16, detectOreIconImageData, 0, 16);
            BufferedImage itemIconBf = ImageIO.read((net.minecraft.client.Minecraft.class).getResource("/gui/items.png"));
            itemIconBf = itemIconBf.getSubimage((itemIconIndex % 16) * 16, (itemIconIndex / 16) * 16, 16, 16);
                        
            /*AffineTransform tx = new AffineTransform();
            tx.scale(0.5, 0.5);
            AffineTransformOp op = new AffineTransformOp(tx,
                    AffineTransformOp.TYPE_BILINEAR);
            BufferedImage biNew = new BufferedImage( (int) (itemIconBf.getWidth() * 0.5),
                    (int) (itemIconBf.getHeight() * 0.5),
                    itemIconBf.getType());
            itemIconBf = op.filter(itemIconBf, biNew);*/
            
            BufferedImage finalIcon = new BufferedImage(16, 16, BufferedImage.TYPE_INT_ARGB);
            Graphics2D g = finalIcon.createGraphics();
            g.drawImage(bufferedimage, 0, 0, null);
            g.drawImage(itemIconBf, 0, 0, 8, 8, null);
            g.dispose();
            
            finalIcon.getRGB(0, 0, 8, 8, detectOreIconImageData, 0, 16);
            detectOreIconImageData = detectOreIconImageData.clone();
        }
        catch(IOException ioexception)
        {
            ioexception.printStackTrace();
        }
    }

    public void onTick()
    {        
        for(int i = 0; i < 256; i++)
        {
            int j = detectOreIconImageData[i] >> 24 & 0xff;
            int k = detectOreIconImageData[i] >> 16 & 0xff;
            int l = detectOreIconImageData[i] >> 8 & 0xff;
            int i1 = detectOreIconImageData[i] >> 0 & 0xff;

            if(anaglyphEnabled)
            {
                int j1 = (k * 30 + l * 59 + i1 * 11) / 100;
                int k1 = (k * 30 + l * 70) / 100;
                int l1 = (k * 30 + i1 * 70) / 100;
                k = j1;
                l = k1;
                i1 = l1;
            }

            imageData[i * 4 + 0] = (byte)k;
            imageData[i * 4 + 1] = (byte)l;
            imageData[i * 4 + 2] = (byte)i1;
            imageData[i * 4 + 3] = (byte)j;
        }
    }
    
    private Minecraft mc;
    private int iDetectedBlockID;
    private int detectOreIconImageData[];
    private double field_4229_i;
    private double field_4228_j;
}
