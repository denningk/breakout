internal i32
Clamp(i32 min, i32 val, i32 max)
{
    if (val < min)
    {
        return min;
    }
    
    if (val > max)
    {
        return max;
    }
    
    return val;
}
