// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import java.util.List;

// Referenced classes of package net.minecraft.src:
//            BiomeGenBase, Block, BiomeDecorator

public class BiomeGenDesert extends BiomeGenBase
{

    public BiomeGenDesert(int i)
    {
        super(i);
        spawnableCreatureList.clear();
        topBlock = (byte)Block.sand.blockID;
        fillerBlock = (byte)Block.sand.blockID;
        field_35488_u.treesPerChunk = -999;
        field_35488_u.deadBushPerChunk = 2;
        field_35488_u.reedsPerChunk = 50;
        field_35488_u.cactiPerChunk = 10;
    }
}
