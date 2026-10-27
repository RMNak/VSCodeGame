const socialMediaLinks = document.getElementById("social-media-links");

try
{
const links = AndroidStudio.socialMediaLinks();
const linkArray = links.split(";");
linkArray.forEach((link) => {
    const linkItem = link.split("&");
    const li = document.createElement("li");
    li.innerHTML = "<a href='" + linkItem[0] + "'> " + linkItem[1] + "</a>";
    socialMediaLinks.appendChild(li);

});
}
catch (error)
{
    console.error("Error fetching social media links:", error);
    const li = document.createElement("li");
    li.innerHTML = "<a href='#'>Error fetching links</a>";
    socialMediaLinks.appendChild(li);
}