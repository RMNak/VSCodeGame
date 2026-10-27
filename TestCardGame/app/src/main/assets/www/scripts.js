const socialMediaLink = document.getElementById("deck")

try{
const link = Android.SocialMediaLinks()
const libraryList = link.split(";");

libraryList.forEach(list => {
const liEt = document.createElement("li");
const linkItem = list.split("&");
liEt.innerHTML = "<a href= " + linkItem[0] + "'>" + linkItem[1] + "</a>"
socialMediaLink.append(liEt)
});
}
catch (e) {
console.log("could not get link " + e);
}

function submitFormReturn(event) {
        event.preventDefault();
      }
       const suits = [
                      { symbol: "♠", class: "black" },
                      { symbol: "♥", class: "red" },
                      { symbol: "♣", class: "black" },
                      { symbol: "♦", class: "red" }
           ];
        const ranks = ['2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K', 'A'];
        const overlap = 20;

        function createDeck() {
            const deck = [];
            for (i = 0; i < 4; i++){
            for (const suit of suits) {
                for (const value of ranks) {
                    deck.push({ suit, value });
                }
            }
        }
            return deck;
        }

        function shuffleDeck(deck) {
            for (let i = deck.length - 1; i > 0; i--) {
                const j = Math.floor(Math.random() * (i + 1));
                [deck[i], deck[j]] = [deck[j], deck[i]];
            }
        }

    // Function to display the deck of cards
    function displayDeck(deck) {
    const deckDiv = document.getElementById("deck");
    deckDiv.innerHTML = "";
    const overlap = 5; // pixels to overlap each card


    deck.forEach((cardObj, i) => {
        const card = document.createElement("div");
        card.className = `card ${cardObj.suit.class}`;
        card.style.left = `${i * overlap}px`;

        // Flippable card structure
        const cardInner = document.createElement("div");
        cardInner.className = "card-inner";

        const cardBack = document.createElement("div");
        cardBack.className = "card-back";
        cardBack.textContent =  `${cardObj.value}${cardObj.suit.symbol}`;

        const cardFront = document.createElement("div");
        cardFront.className = "card-front";
        cardFront.textContent = "🂠";

        cardInner.appendChild(cardFront);
        cardInner.appendChild(cardBack);

        card.appendChild(cardInner);

        var YValue = 20;
        card.addEventListener("click", () => {
          document.querySelectorAll('.card').forEach(c => c.style.zIndex = 0);
          card.style.zIndex = 1000;
          card.classList.toggle("flipped");
          YValue += 4.555;
          if (i % 2 === 0) {
            card.style.transform = `translateX(${YValue * 20 + i * 5}px)`;
            card.style.transform = `translateY(${YValue * 5 + i}px)`;
            var audio = new Audio('C:\\VSCodeExample\\Game\\css-deck-of-cards\\andarf.mp3');
            audio.play();
            //card.style.pointerEvents = 'none';
          }
          else {
              card.style.transform = `translateX(${YValue * 5 + i}px)`;
              card.style.transform = `translateY(${YValue * 20 + i}px)`;
              var audio = new Audio('C:\\VSCodeExample\\Game\\css-deck-of-cards\\baharf.mp3');
              audio.play();
              //card.style.pointerEvents = 'none';
          }
        });

        deckDiv.appendChild(card);

    });
}

        const deck = createDeck();
        shuffleDeck(deck);
        displayDeck(deck);

        window.onbeforeunload = function()
        {
          let result = confirm("Dude, are you sure you want to leave? Think of the kittens!");
          if (result) {
            return true;
          }
          else {
            return false;
          }
        };