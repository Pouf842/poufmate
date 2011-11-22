// Decompiled by Jad v1.5.8g. Copyright 2001 Pavel Kouznetsov.
// Jad home page: http://www.kpdus.com/jad.html
// Decompiler options: packimports(3) braces deadcode 

package net.minecraft.src;

import java.util.Random;

// Referenced classes of package net.minecraft.src:
//            WorldGenerator, Block, World, Material

public class WorldGenClay extends WorldGenerator
{

    public WorldGenClay(int i)
    {
        clayBlockId = Block.blockClay.blockID;
        numberOfBlocks = i;
    }

    public boolean generate(World world, Random random, int i, int j, int k)
    {
        if(world.getBlockMaterial(i, j, k) != Material.water)
        {
            return false;
        }
        int l = random.nextInt(numberOfBlocks - 2) + 2;
        int i1 = 1;
        for(int j1 = i - l; j1 <= i + l; j1++)
        {
            for(int k1 = k - l; k1 <= k + l; k1++)
            {
                int l1 = j1 - i;
                int i2 = k1 - k;
                if(l1 * l1 + i2 * i2 > l * l)
                {
                    continue;
                }
                for(int j2 = j - i1; j2 <= j + i1; j2++)
                {
                    int k2 = world.getBlockId(j1, j2, k1);
                    if(k2 == Block.dirt.blockID || k2 == Block.blockClay.blockID)
                    {
                        world.setBlock(j1, j2, k1, clayBlockId);
                    }
                }

            }

        }

        return true;
    }

    private int clayBlockId;
    private int numberOfBlocks;
}
