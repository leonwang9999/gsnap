<%@ LANGUAGE="VBSCRIPT" %>
<HTML>
<HEAD>
<META HTTP-EQUIV="Content-Type" content="text/html; charset=iso-8859-1">
<TITLE>Simple File Upload Results</TITLE>
</HEAD>
<BODY>
<p>
  <%
Set upl = Server.CreateObject("SoftArtisans.FileUp")
upl.Path = "d:\web\client\charry\wwwroot\test"
%>
  <% if upl.IsEmpty Then %>
&#20320;&#36873;&#25321;&#30340;&#25991;&#20214;&#26159;&#20010;&#31354;&#25991;&#20214;&#65292; &#24744;&#36755;&#20837;&#30340;&#21487;&#33021;&#26159;&#19968;&#20010;&#26080;&#25928;&#30340;&#25991;&#20214;&#21517;&#65292;&#35831;&#37325;&#26032;&#26469;&#36807;&#12290;
<% ElseIf upl.ContentDisposition <> "form-data" Then %>
&#19978;&#20256;&#22833;&#36133;&#65292;&#21407;&#22240;&#21487;&#33021;&#26159;&#22240;&#20026;&#20320;&#30340;&#27983;&#35272;&#22120;&#19981;&#25903;&#25345;&#12290;<br>
</p>
<%Else %>
<%

%>
<P>&#24863;&#35874;&#24744;&#19978;&#20256;MSN&#36164;&#28304;&#25991;&#20214;</P>
<% 

	on error resume next
	'---
	'--- Save the file now. If you want to preserve the original user's filename, use
	'---
	upl.Save

	'---
	'--- OR, if you want set your own name, uncomment one of the below lines
	'---
	'--- upl.SaveAs "upload.tst" '--- this uses .Path property
	'--- upl.SaveAs "d:\someotherdir\myfile.ext"
	'--- upl.SaveAs "\\bowser\calendar\myfile.ext"	'--- NOTE: The anonymous user *must* have network 
													'--- access rights for UNC names to work
	if Err <> 0 Then %>
<H1><FONT COLOR="#ff0000">An error occurred when saving the file on the server.</FONT></H1>
Possible causes include:
<UL>
  <LI>An incorrect filename was specified
  <LI>File permissions do not allow writing to the specified area
</UL>
Please check the SA-FileUp documentation for more troubleshooting information,
or send e-mail to <A HREF="mailto:info@softartisans.com">info@softartisans.com</A>

<%	Else 
		'Response.Write("Upload saved successfully to " & upl.ServerName)
	End If %>
<P>&nbsp;</P>
<FONT SIZE="-1"><CENTER>
<TABLE WIDTH="80%" BORDER="1" CELLSPACING="2" CELLPADDING="0" HEIGHT="206">
<TR>
<TD COLSPAN="2"><P><CENTER>
  &#25991;&#20214;&#20449;&#24687;
</CENTER></TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">&#25991;&#20214;&#21517;</TD>
<TD WIDTH="70%"><%=upl.UserFilename%>&nbsp;</TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">&#22823;&#23567;(bytes)&nbsp;</TD>
<TD WIDTH="70%"><%=upl.TotalBytes%>&nbsp;</TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">&#20869;&#23481;&#31867;&#22411;</TD>
<TD WIDTH="70%"><%=upl.ContentType%>&nbsp;</TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">&#20869;&#23481;&#25551;&#36848;</TD>
<TD WIDTH="70%"><%=upl.ContentDisposition%>&nbsp;</TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">MIME Version</TD>
<TD WIDTH="70%"><%=upl.MimeVersion%>&nbsp;</TD></TR>
<TR>
<TD WIDTH="30%" HEIGHT="27" ALIGN="RIGHT" VALIGN="TOP">Content Transfer Encoding</TD>
<TD WIDTH="70%"><%=upl.ContentTransferEncoding%>&nbsp;</TD></TR>
</TABLE>
</CENTER>
<% End If %>
</BODY>
</HTML>
