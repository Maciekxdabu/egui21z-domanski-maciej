namespace trs.Models;

public class MIndexModel
{
    public string date { get; set; }//date of the monthly report
    public List<MEntry> tableEntries { get; set; }//list of entries for the table
}

public class MEntry
    {
        public string projectName { get; set; }
        public string projectCode { get; set; }
        public int timeSpent { get; set; }
    }