// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import org.lwjgl.opengl.GL11;
import org.lwjgl.opengl.GL13;

// Referenced classes of package net.minecraft.src:
//            RenderLiving, ModelSpider, EntitySpider, EntityLiving

public class RenderSpider extends RenderLiving
{

    public RenderSpider()
    {
        super(new ModelSpider(), 1.0F);
        setRenderPassModel(new ModelSpider());
    }

    protected float setSpiderDeathMaxRotation(EntitySpider entityspider)
    {
        return 180F;
    }

    protected boolean setSpiderEyeBrightness(EntitySpider entityspider, int i, float f)
    {
        if(i != 0)
        {
            return false;
        }
        if(i != 0)
        {
            return false;
        } else
        {
            loadTexture("/mob/spider_eyes.png");
            float f1 = 1.0F;
            GL11.glEnable(3042 /*GL_BLEND*/);
            GL11.glDisable(3008 /*GL_ALPHA_TEST*/);
            GL11.glBlendFunc(1, 1);
            int j = 61680;
            int k = j % 0x10000;
            int l = j / 0x10000;
            GL13.glMultiTexCoord2f(33985 /*GL_TEXTURE1_ARB*/, (float)k / 1.0F, (float)l / 1.0F);
            GL11.glColor4f(1.0F, 1.0F, 1.0F, 1.0F);
            GL11.glColor4f(1.0F, 1.0F, 1.0F, f1);
            return true;
        }
    }

    protected void func_35446_a(EntitySpider entityspider, float f)
    {
        float f1 = entityspider.func_35188_k_();
        GL11.glScalef(f1, f1, f1);
    }

    protected void preRenderCallback(EntityLiving entityliving, float f)
    {
        func_35446_a((EntitySpider)entityliving, f);
    }

    protected float getDeathMaxRotation(EntityLiving entityliving)
    {
        return setSpiderDeathMaxRotation((EntitySpider)entityliving);
    }

    protected boolean shouldRenderPass(EntityLiving entityliving, int i, float f)
    {
        return setSpiderEyeBrightness((EntitySpider)entityliving, i, f);
    }
}
