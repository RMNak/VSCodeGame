package com.example.cardgame

import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private val deck = mutableListOf<String>()
    private lateinit var cardTextView: TextView

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        cardTextView = findViewById(R.id.cardTextView)
        val drawCardButton: Button = findViewById(R.id.drawCardButton)

        initializeDeck()

        drawCardButton.setOnClickListener {
            drawCard()
        }
    }

    private fun initializeDeck() {
        val suits = listOf("Hearts", "Diamonds", "Clubs", "Spades")
        val values = listOf("2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace")

        for (suit in suits) {
            for (value in values) {
                deck.add("$value of $suit")
            }
        }

        deck.shuffle()
    }

    private fun drawCard() {
        if (deck.isNotEmpty()) {
            val card = deck.removeAt(0)
            cardTextView.text = card
        } else {
            cardTextView.text = "No more cards in the deck"
        }
    }
}