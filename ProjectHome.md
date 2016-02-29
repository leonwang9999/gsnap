### Project Info ###
GSnap is a snapshot tool, it will save the image to your local directory and upload it to your specified web server and copy the url to your clipboard in the meantime, when you click 'Capture'. if Google Talk is running on your computer, it also bring GTalk upmost.

Programming language: C++(MFC)

IDE: MS VC6, MS2005

GSnap integrates the following open source libs:
  * [CxImage](http://www.codeproject.com/KB/graphics/cximage.aspx)
  * [CXmlDocumentWrapper](http://www.codeproject.com/KB/trace/C___XML_wrapper.aspx)
  * [SnaperHelper](http://www.codeproject.com/KB/cpp/screen_snaper.aspx)
Thanks the developers who wrote the powerful above components.

Before you try GSnap, please edit your g.xml, below is a sample for you:

```
<?xml version="1.0" encoding="GBK"?>
<gsnap server="googlestop.com" uploadpath="gsnap" url="upload_99239237DJJSDH_--SDF.php"  port="80" tagname="file1"></gsnap>
```

### Developer ###
  * Charry

### History ###
2007-03 release 1.0