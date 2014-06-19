public class SegmentTreeRangeUpdate {
	public long[] leaf;
	public long[] update;
	public int origSize;
	public SegmentTreeRangeUpdate(int[] list)	{
		origSize = list.length;
		leaf = new long[4*list.length];
		update = new long[4*list.length];
		build(1,0,list.length-1,list);
	}
	public void build(int curr, int begin, int end, int[] list)	{
		if(begin == end)
			leaf[curr] = list[begin];
		else	{
			int mid = (begin+end)/2;
			build(2 * curr, begin, mid, list);
			build(2 * curr + 1, mid+1, end, list);
			leaf[curr] = leaf[2*curr] + leaf[2*curr+1];
		}
	}
	public void update(int begin, int end, int val)	{
		update(1,0,origSize-1,begin,end,val);
	}
	public void update(int curr,  int tBegin, int tEnd, int begin, int end, int val)	{
		if(tBegin >= begin && tEnd <= end)
			update[curr] += val;
		else	{
			leaf[curr] += (Math.min(end,tEnd)-Math.max(begin,tBegin)+1) * val;
			int mid = (tBegin+tEnd)/2;
			if(mid >= begin && tBegin <= end)
				update(2*curr, tBegin, mid, begin, end, val);
			if(tEnd >= begin && mid+1 <= end)
				update(2*curr+1, mid+1, tEnd, begin, end, val);
		}
	}
	public long query(int begin, int end)	{
		return query(1,0,origSize-1,begin,end);
	}
	public long query(int curr, int tBegin, int tEnd, int begin, int end)	{
		if(tBegin >= begin && tEnd <= end)	{
			if(update[curr] != 0)	{
				leaf[curr] += (tEnd-tBegin+1) * update[curr];
				if(2*curr < update.length){
					update[2*curr] += update[curr];
					update[2*curr+1] += update[curr];
				}
				update[curr] = 0;
			}
			return leaf[curr];
		}
		else	{
			leaf[curr] += (tEnd-tBegin+1) * update[curr];
			if(2*curr < update.length){
				update[2*curr] += update[curr];
				update[2*curr+1] += update[curr];
			}
			update[curr] = 0;
			int mid = (tBegin+tEnd)/2;
			long ret = 0;
			if(mid >= begin && tBegin <= end)
				ret += query(2*curr, tBegin, mid, begin, end);
			if(tEnd >= begin && mid+1 <= end)
				ret += query(2*curr+1, mid+1, tEnd, begin, end);
			return ret;
		}
	}
}