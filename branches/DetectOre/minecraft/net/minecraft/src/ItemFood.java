// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import java.util.Random;

// Referenced classes of package net.minecraft.src:
//            Item, ItemStack, EntityPlayer, FoodStats, 
//            World, PotionEffect, EnumAction

public class ItemFood extends Item
{

    public ItemFood(int i, int j, float f, boolean flag)
    {
        super(i);
        healAmount = j;
        isWolfsFavoriteMeat = flag;
        saturationModifier = f;
    }

    public ItemFood(int i, int j, boolean flag)
    {
        this(i, j, 0.6F, flag);
    }

    public ItemStack onFoodEaten(ItemStack itemstack, World world, EntityPlayer entityplayer)
    {
        itemstack.stackSize--;
        entityplayer.getFoodStats().addStatsFrom(this);
        if(!world.multiplayerWorld && field_35433_bx > 0 && world.rand.nextFloat() < field_35429_bA)
        {
            entityplayer.addPotionEffect(new PotionEffect(field_35433_bx, field_35432_by * 20, field_35427_bz));
        }
        return itemstack;
    }

    public int getMaxItemUseDuration(ItemStack itemstack)
    {
        return 32;
    }

    public EnumAction getItemUseAction(ItemStack itemstack)
    {
        return EnumAction.eat;
    }

    public ItemStack onItemRightClick(ItemStack itemstack, World world, EntityPlayer entityplayer)
    {
        if(entityplayer.func_35197_b(field_35431_bw))
        {
            entityplayer.setItemInUse(itemstack, getMaxItemUseDuration(itemstack));
        }
        return itemstack;
    }

    public int getHealAmount()
    {
        return healAmount;
    }

    public float getSaturationModifier()
    {
        return saturationModifier;
    }

    public boolean getIsWolfsFavoriteMeat()
    {
        return isWolfsFavoriteMeat;
    }

    public ItemFood setPotionEffect(int i, int j, int k, float f)
    {
        field_35433_bx = i;
        field_35432_by = j;
        field_35427_bz = k;
        field_35429_bA = f;
        return this;
    }

    public ItemFood func_35424_o()
    {
        field_35431_bw = true;
        return this;
    }

    public Item setItemName(String s)
    {
        return super.setItemName(s);
    }

    public final int field_35430_a = 32;
    private final int healAmount;
    private final float saturationModifier;
    private final boolean isWolfsFavoriteMeat;
    private boolean field_35431_bw;
    private int field_35433_bx;
    private int field_35432_by;
    private int field_35427_bz;
    private float field_35429_bA;
}
